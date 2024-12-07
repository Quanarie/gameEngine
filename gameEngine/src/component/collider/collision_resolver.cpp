#include "component/collider/collision_resolver.h"

#include <array>
#include <vector>
#include <__algorithm/clamp.h>

#include "inputs.h"
#include "component/transform_component.h"
#include "component/collider/ellipse/ellipse_colider_component.h"
#include "component/collider/rectangle/rectangle_colider_component.h"
#include "component/collider/rectangle/rectangle_corners.h"
#include "math/point.h"

#define RECTANGLE_CORNERS_COUNT 4
#define MAX_SIDES_CONTAINING_SAME_POINT 2

struct OverlapResult {
  bool doesOverlap;
  Point shortestOverlapResolutionVector;
  float overlapValue;
};

// std::optional<Point> findLineIntersectionPoint(Point a1, Point b1, Point a2, Point b2) {
//   float s1_x, s1_y, s2_x, s2_y;
//   s1_x = b1.x - a1.x;
//   s1_y = b1.y - a1.y;
//   s2_x = b2.x - a2.x;
//   s2_y = b2.y - a2.y;
//
//   float s, t;
//   s = (-s1_y * (a1.x - a2.x) + s1_x * (a1.y - a2.y)) / (-s2_x * s1_y + s1_x * s2_y);
//   t = (s2_x * (a1.y - a2.y) - s2_y * (a1.x - a2.x)) / (-s2_x * s1_y + s1_x * s2_y);
//
//   if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
//     return Point{a1.x + (t * s1_x), a1.y + (t * s1_y)};
//   }
//
//   return std::nullopt;
// }
//
// bool doSegmentsIntersect(Point a1, Point b1, Point a2, Point b2) {
//   // Find point where lines intersect and check if its in bounds of each segment
//   std::optional<Point> lineIntersect = findLineIntersectionPoint(a1, b1, a2, b2);
//   if (!lineIntersect.has_value())
//     return false;
//
//   return lineIntersect->isInsideSegment(a1, a2);
// }
//
// bool doesSegmentIntersectRectangle(Point a, Point b, std::array<Point, 4> rect) {
//   for (int i = 0; i < rect.size(); i++) {
//     Point segmentStart = rect[i];
//     Point segmentEnd = rect[(i + 1) % 4];
//
//     if (doSegmentsIntersect(a, b, segmentStart, segmentEnd))
//       return true;
//   }
//
//   return false;
// }

// TODO: implement for rotated rectangles
// bool doRectanglesIntersect(std::array<Point, 4> rect1, std::array<Point, 4> rect2) {
//   for (int i = 0; i < rect1.size(); i++) {
//     Point segmentStart = rect1[i];
//     Point segmentEnd = rect1[(i + 1) % 4];
//
//     if (doesSegmentIntersectRectangle(segmentStart, segmentEnd, rect2))
//       return true;
//   }
//
//   return false;
// }

// Only axis aligned rectangles
bool doRectanglesIntersect(RectangleCorners rect1, RectangleCorners rect2) {
  float rect1MinX = rect1[0].x;
  float rect1MaxX = rect1[3].x;
  float rect1MinY = rect1[2].y;
  float rect1MaxY = rect1[0].y;

  float rect2MinX = rect2[0].x;
  float rect2MaxX = rect2[3].x;
  float rect2MinY = rect2[2].y;
  float rect2MaxY = rect2[0].y;

  bool xOverlap = rect1MaxX > rect2MinX && rect2MaxX > rect1MinX;
  bool yOverlap = rect1MaxY > rect2MinY && rect2MaxY > rect1MinY;

  return xOverlap && yOverlap;
}

OverlapResult doesRectCornerOverlapOtherRect(RectangleCorners rect1Corners, int cornerIndex,
                                             RectangleCorners rect2Corners) {
  Point corner = rect1Corners[cornerIndex];

  float minDistance = std::numeric_limits<float>::max();
  Point shortestResolutionVector = {0, 0};

  for (int i = 0; i < RECTANGLE_CORNERS_COUNT; i++) {
    Point segmentStart = rect2Corners[i];
    Point segmentEnd = rect2Corners[(i + 1) % 4];

    Point projectedPoint = corner.projectPointOntoLine(segmentStart, segmentEnd);
    if (!projectedPoint.isOnSegment(segmentStart, segmentEnd))
      return {
        false,
        Point{std::numeric_limits<float>::max(), std::numeric_limits<float>::max()},
        std::numeric_limits<float>::max()
      };

    Point resolutionVector = projectedPoint - corner;
    float distance = resolutionVector.length();

    // This prevents jiggling bugs where one side of rect is close another, and they go inside each other
    RectangleCorners rect1CornersResolved = {};
    RectangleCorners rect2CornersResolved = {};
    for (int j = 0; j < RECTANGLE_CORNERS_COUNT; j++) {
      rect1CornersResolved[j] = rect1Corners[j] + resolutionVector / 2;
      rect2CornersResolved[j] = rect2Corners[j] - resolutionVector / 2;
    }

    if (distance < minDistance) {
      if (doRectanglesIntersect(rect1CornersResolved, rect2CornersResolved))
        continue;
      minDistance = distance;
      shortestResolutionVector = resolutionVector;
    }
  }

  return {true, shortestResolutionVector, minDistance};
}

bool checkAnyCornerOfRect1InsideRect2AndResolve(const RectangleColliderComponent& rect1,
                                                TransformComponent& trans1,
                                                const RectangleColliderComponent& rect2,
                                                TransformComponent& trans2) {
  auto rect1Corners = rect1.getTransformedCorners(trans1.position);
  auto rect2Corners = rect2.getTransformedCorners(trans2.position);

  OverlapResult minOverlapResult = doesRectCornerOverlapOtherRect(rect1Corners, 0, rect2Corners);
  for (int i = 1; i < RECTANGLE_CORNERS_COUNT; i++) {
    OverlapResult overlapResult = doesRectCornerOverlapOtherRect(rect1Corners, i, rect2Corners);
    if (overlapResult.doesOverlap && overlapResult.overlapValue < minOverlapResult.overlapValue) {
      minOverlapResult = overlapResult;
    }
  }

  if (!minOverlapResult.doesOverlap)
    return false;

  trans1.position = trans1.position + minOverlapResult.shortestOverlapResolutionVector / 2;
  trans2.position = trans2.position - minOverlapResult.shortestOverlapResolutionVector / 2;

  return true;
}

// Create tests for this pls
bool CollisionResolver::resolve(const RectangleColliderComponent& rect1,
                                TransformComponent& trans1,
                                const RectangleColliderComponent& rect2,
                                TransformComponent& trans2) {
  // We need to check if any corner of rect1 is in rect2 or vice versa, cuz rectangles can be rotated (in future)
  if (checkAnyCornerOfRect1InsideRect2AndResolve(rect1, trans1, rect2, trans2))
    return true;

  if (checkAnyCornerOfRect1InsideRect2AndResolve(rect2, trans2, rect1, trans1))
    return true;

  return false;
}

struct Line {
  float slope;
  float yIntercept;
};

std::optional<Line> getLineDefinedByTwoPoints(Point p, Point q) {
  if (p.x == q.x)
    return std::nullopt;

  float angle = (q.y - p.y) / (p.x - q.x);
  return Line{
    angle,
    p.x * angle + p.y
  };
}

struct CornerInfo {
  bool isCorner = false;
  Point prevPoint;
  Point point;
  Point nextPoint;
};

std::vector<std::optional<Line>> getLinesDefinedBySidesThatContainsPoint(CornerInfo cornerInfo) {
  std::vector<std::optional<Line>> res{};

  if (cornerInfo.isCorner) {
    res.push_back(getLineDefinedByTwoPoints(cornerInfo.prevPoint, cornerInfo.point));
  }
  res.push_back(getLineDefinedByTwoPoints(cornerInfo.point, cornerInfo.nextPoint));

  return res;
}

std::array<Point, 2> getIntersectionsOfLineAndEllipse(Line line, Point ellipCenter, EllipseAxes axes) {
  Point intersect1, intersect2;
  float sl = line.slope;
  float yI = line.yIntercept - ellipCenter.y;
  float j = axes.sMajor;
  float m = axes.sMinor;

  float x1, x2;
  if (sl == 0.0f) {
    x1 = sqrt(j * j * (1 - pow(yI / m, 2)));
  }
  else {
    float a = m * m + sl * sl * j * j;
    float b = 2 * j * j * sl * yI;
    float c = j * j * b * b - j * j * m * m;
    float delta = b * b - 4 * a * c;
    if (delta <= 0) {
      throw std::runtime_error("Expected a solution but none was found.");
    }

    x1 = (-b + sqrt(delta)) / (2 * a);
  }

  intersect1 = Point{
    x1,
    // minus because different coordinate systems. Fucking math works in regular coordinates
    -sl * x1 + yI
  } + ellipCenter;


  // тут оказується більше не той який має бути для лівого верхнього кута вліво

  x2 = -x1;
  intersect2 = Point{x2, -sl * x2 + yI} + ellipCenter;

  return std::array{intersect1, intersect2};
}

std::optional<Line> getPerpendicularLineToSegmentAtPoint(Point point, std::optional<Line> lineOpt) {
  if (!lineOpt.has_value())
    return Line{0.0f, point.y};

  if (lineOpt->slope == 0.0f)
    return std::nullopt;

  Line line = lineOpt.value();
  return Line{-line.slope, point.y + line.slope * point.x};
}

Point getClosestPointToPoint(std::array<Point, 2> intersections, Point point) {
  if ((intersections[0] - point).length() < (intersections[1] - point).length())
    return intersections[0];

  return intersections[1];
}

CornerInfo isCorner(Point point, RectangleCorners rect) {
  int howManySidesContainPoint = 0;
  CornerInfo res{};
  for (int i = 0; i < RECTANGLE_CORNERS_COUNT; i++) {
    Point sideStart = rect[i];
    Point sideEnd = rect[(i + 1) % 4];

    if (point.isOnSegment(sideStart, sideEnd)) {
      howManySidesContainPoint++;
      res = CornerInfo{false, sideStart, sideStart, sideEnd};
      if (howManySidesContainPoint == 2) {
        res = CornerInfo{true, rect[(i - 1) % 4], sideStart, sideEnd};
        return res;
      }
    }
  }

  return res;
}

bool isSideVertical(Point start, Point end) {
  return start.x == end.x;
}

bool CollisionResolver::resolve(const EllipseColliderComponent& ellip,
                                TransformComponent& transEllip,
                                const RectangleColliderComponent& rect,
                                TransformComponent& transRect) {
  Point ellipCenter = ellip.getTransformedCenter(transEllip.position);
  auto rectCorners = rect.getTransformedCorners(transRect.position);

  auto closestPointToEllipInRect = Point{
    std::clamp(ellipCenter.x, rectCorners.ld.x, rectCorners.ru.x),
    std::clamp(ellipCenter.y, rectCorners.ru.y, rectCorners.ld.y)
  };

  auto relativeToEllip = closestPointToEllipInRect - ellipCenter;

  if (relativeToEllip.x * relativeToEllip.x / (ellip.axes.sMajor * ellip.axes.sMajor) +
    relativeToEllip.y * relativeToEllip.y / (ellip.axes.sMinor * ellip.axes.sMinor) >= 1)
    return false;

  std::vector<std::optional<Line>> linesContainingClosestPoint =
    getLinesDefinedBySidesThatContainsPoint(isCorner(closestPointToEllipInRect, rectCorners));

  Point resolutionVector{0.0f, 0.0f};
  float weightSum = 0.0f;

  // TODO: Try to take two point of intersection, get perpen in middle of it as resolutionVector
  // That would eliminate the need for this cycle
  for (auto line : linesContainingClosestPoint) {
    std::optional<Line> perperndicularToLineContClosestPoint = getPerpendicularLineToSegmentAtPoint(
      closestPointToEllipInRect, line);

    std::array<Point, 2> intersections;
    if (perperndicularToLineContClosestPoint.has_value()) {
      intersections = getIntersectionsOfLineAndEllipse(
        perperndicularToLineContClosestPoint.value(),
        ellipCenter,
        ellip.axes
      );
    }
    else {
      float y0 = ellip.axes.sMinor * sqrt(1 - pow(relativeToEllip.x / ellip.axes.sMajor, 2));
      intersections[0] = Point{relativeToEllip.x, y0} + ellipCenter;
      intersections[1] = Point{relativeToEllip.x, -y0} + ellipCenter;
    }

    Point closestIntersection = getClosestPointToPoint(intersections, closestPointToEllipInRect);
    Point currentResolutionVector = closestPointToEllipInRect - closestIntersection;

    float weight = 1.0f / (1.0f + std::abs(currentResolutionVector.length() - resolutionVector.length()));
    resolutionVector = resolutionVector + (currentResolutionVector * weight);
    weightSum += weight;
  }

  if (weightSum > 0.0f) {
    resolutionVector = resolutionVector * (1.0f / weightSum);
  }

  transEllip.position = transEllip.position + resolutionVector / 2;
  transRect.position = transRect.position - resolutionVector / 2;

  return true;
}

bool CollisionResolver::resolve(const EllipseColliderComponent& ell1,
                                TransformComponent& trans1,
                                const EllipseColliderComponent& ell2,
                                TransformComponent& trans2) {
  Point ell1Center = ell1.center + trans1.position;
  Point ell2Center = ell2.center + trans2.position;

  // Treating 2 center as a point we should check to lie within a "combined" ellipse
  // Intuitively: we can shrink second ellipse and expand first as much till second becomes just a point
  // Curvature of ellipses are same so shrinking and expanding is equivalent
  Point center2RelatTo1 = Point{
    ell2Center.x - ell1Center.x,
    ell2Center.y - ell1Center.y
  };

  Point combinedRads = Point{
    ell1.axes.sMajor + ell2.axes.sMajor,
    ell1.axes.sMinor + ell2.axes.sMinor
  };

  if (center2RelatTo1.x * center2RelatTo1.x / (combinedRads.x * combinedRads.x) +
    center2RelatTo1.y * center2RelatTo1.y / (combinedRads.y * combinedRads.y) <= 1)
    return false;
}
