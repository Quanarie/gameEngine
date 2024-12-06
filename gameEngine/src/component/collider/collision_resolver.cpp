#include "component/collider/collision_resolver.h"

#include <array>
#include <vector>
#include <__algorithm/clamp.h>

#include "component/transform_component.h"
#include "component/collider/ellipse/ellipse_colider_component.h"
#include "component/collider/rectangle_colider_component.h"
#include "math/point.h"

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
bool doRectanglesIntersect(std::array<Point, 4> rect1, std::array<Point, 4> rect2) {
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

OverlapResult doesPointOverlapRect(std::array<Point, 4> rect1Corners, int cornerIndex,
                                   std::array<Point, 4> rect2Corners) {
  Point corner = rect1Corners[cornerIndex];

  float minDistance = std::numeric_limits<float>::max();
  Point shortestResolutionVector = {0, 0};

  for (int i = 0; i < rect2Corners.size(); i++) {
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
    std::array<Point, 4> rect1CornersResolved = {};
    std::array<Point, 4> rect2CornersResolved = {};
    for (int j = 0; j < rect1Corners.size(); j++) {
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

  OverlapResult minOverlapResult = doesPointOverlapRect(rect1Corners, 0, rect2Corners);
  for (int i = 1; i < rect1Corners.size(); i++) {
    OverlapResult overlapResult = doesPointOverlapRect(rect1Corners, i, rect2Corners);
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


Point getEllipAndPointCenterDefinedLineClosestIntersectionPoint(Point ellipCenter,
                                                                EllipseAxes axes,
                                                                Point point) {
  std::optional<Line> line = getLineDefinedByTwoPoints(Point{0.0f, 0.0f}, point - ellipCenter);

  Point intersect1, intersect2;
  if (line.has_value()) {
    float sl = line.value().slope;
    float yI = line.value().yIntercept;
    float j = axes.sMajor;
    float m = axes.sMinor;

    float a = m * m + sl * sl * j * j;
    float b = 2 * j * j * sl * yI;
    float c = j * j * b * b - j * j * m * m;
    float delta = b * b - 4 * a * c;
    if (delta <= 0) {
      throw std::runtime_error("Expected a solution but none was found.");
    }

    float x1 = (-b + sqrt(delta)) / (2 * a);

    intersect1 = Point{
      x1,
      // minus because different coordinate systems. Fucking math works in regular coordinates
      -sl * x1 + yI
    } + ellipCenter;

    float x2 = (-b - sqrt(delta)) / (2 * a);
    intersect2 = Point{x2, -sl * x2 + yI} + ellipCenter;
  }
  else {
    intersect1 = Point{0, axes.sMinor} + ellipCenter;
    intersect2 = Point{0, -axes.sMinor} + ellipCenter;
  }

  float lengthToIntersect1 = (intersect1 - point).length();
  float lengthToIntersect2 = (intersect2 - point).length();

  if (lengthToIntersect1 < lengthToIntersect2) {
    return intersect1;
  }

  return intersect2;
}


// Axis aligned rect and not rotated ellipse :(
bool CollisionResolver::resolve(const EllipseColliderComponent& ellip,
                                TransformComponent& transEllip,
                                const RectangleColliderComponent& rect,
                                TransformComponent& transRect) {
  Point ellipCenter = ellip.getTransformedCenter(transEllip.position);
  auto [rectLD, rectRU] = rect.getTransformedDefiningCorners(transRect.position);

  auto closestPointToEllipInRect = Point{
    std::clamp(ellipCenter.x, rectLD.x, rectRU.x),
    std::clamp(ellipCenter.y, rectRU.y, rectLD.y)
  };

  auto relativeToEllip = Point{
    ellipCenter.x - closestPointToEllipInRect.x,
    ellipCenter.y - closestPointToEllipInRect.y
  };

  if (relativeToEllip.x * relativeToEllip.x / (ellip.axes.sMajor * ellip.axes.sMajor) +
    relativeToEllip.y * relativeToEllip.y / (ellip.axes.sMinor * ellip.axes.sMinor) >= 1)
    return false;

  // Find intersection of ellipCetner - closestPoint line. Then find length of segment that is between
  // intersection and closestPoint. This is resolutionVector

  Point intersectionPoint = getEllipAndPointCenterDefinedLineClosestIntersectionPoint(
    ellipCenter, ellip.axes, closestPointToEllipInRect);
  Point resolutionVector = closestPointToEllipInRect - intersectionPoint;

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

  Point intersectionPoint = Point{

  };
}
