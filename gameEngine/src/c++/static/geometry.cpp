#include "static/geometry.h"

#include <limits>
#include <optional>
#include <vector>

#include "util/vector.h"
#include "component/collider/ellipse/ellipse_axes.h"
#include "component/collider/rectangle/rectangle_corners.h"

#define RECTANGLE_CORNERS_COUNT 4
#define MAX_SIDES_CONTAINING_SAME_POINT 2
#define TREAT_AS_GOING_THROUGH_ELLIPSE_CENTER 0.25f

std::optional<Vector> Geometry::findLineIntersectionPoint(Vector a1, Vector b1, Vector a2, Vector b2) {
  float s1_x, s1_y, s2_x, s2_y;
  s1_x = b1.x - a1.x;
  s1_y = b1.y - a1.y;
  s2_x = b2.x - a2.x;
  s2_y = b2.y - a2.y;

  float s, t;
  s = (-s1_y * (a1.x - a2.x) + s1_x * (a1.y - a2.y)) / (-s2_x * s1_y + s1_x * s2_y);
  t = (s2_x * (a1.y - a2.y) - s2_y * (a1.x - a2.x)) / (-s2_x * s1_y + s1_x * s2_y);

  if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
    return Vector{a1.x + (t * s1_x), a1.y + (t * s1_y)};
  }

  return std::nullopt;
}

static bool doSegmentsIntersect(Vector a1, Vector b1, Vector a2, Vector b2) {
  // Find point where lines intersect and check if its in bounds of each segment
  std::optional<Vector> lineIntersect = Geometry::findLineIntersectionPoint(a1, b1, a2, b2);
  if (!lineIntersect.has_value())
    return false;

  return lineIntersect->isOnSegment(a1, a2);
}

static bool doesSegmentIntersectRectangle(Vector a, Vector b, RectangleCorners rect) {
  for (int i = 0; i < RECTANGLE_CORNERS_COUNT; i++) {
    Vector segmentStart = rect[i];
    Vector segmentEnd = rect[(i + 1) % 4];

    if (doSegmentsIntersect(a, b, segmentStart, segmentEnd))
      return true;
  }

  return false;
}

static bool doRectanglesIntersect(RectangleCorners rect1, RectangleCorners rect2) {
  for (int i = 0; i < RECTANGLE_CORNERS_COUNT; i++) {
    Vector segmentStart = rect1[i];
    Vector segmentEnd = rect1[(i + 1) % 4];

    if (doesSegmentIntersectRectangle(segmentStart, segmentEnd, rect2))
      return true;
  }

  return false;
}

OverlapResult Geometry::doesRectCornerOverlapOtherRect(RectangleCorners rect1Corners, int cornerIndex,
                                                       RectangleCorners rect2Corners)
{
  Vector corner = rect1Corners[cornerIndex];
  Vector shortestResolutionVector = {std::numeric_limits<float>::max(), 0};

  for (int i = 0; i < RECTANGLE_CORNERS_COUNT; i++)
  {
    Vector segmentStart = rect2Corners[i];
    Vector segmentEnd = rect2Corners[(i + 1) % 4];

    Vector projectedPoint = corner.projectPointOntoLine(segmentStart, segmentEnd);
    if (!projectedPoint.isOnSegment(segmentStart, segmentEnd))
      return {false, shortestResolutionVector};

    Vector resolutionVector = projectedPoint - corner;

    // This prevents jiggling bugs where one side of rect is close another, and they go inside each other
    RectangleCorners rect1CornersResolved = {};
    RectangleCorners rect2CornersResolved = {};
    for (int j = 0; j < RECTANGLE_CORNERS_COUNT; j++)
    {
      rect1CornersResolved[j] = rect1Corners[j] + resolutionVector / 2;
      rect2CornersResolved[j] = rect2Corners[j] - resolutionVector / 2;
    }

    if (resolutionVector.length() < shortestResolutionVector.length())
    {
      if (doRectanglesIntersect(rect1CornersResolved, rect2CornersResolved))
        continue;
      shortestResolutionVector = resolutionVector;
    }
  }

  return {true, shortestResolutionVector};
}

OverlapResult Geometry::anyCornerOfRect1InsideRect2(const RectangleCorners& rect1Corners,
                                                    const RectangleCorners& rect2Corners)
{
  OverlapResult minOverlapResult = doesRectCornerOverlapOtherRect(rect1Corners, 0, rect2Corners);
  for (int i = 1; i < RECTANGLE_CORNERS_COUNT; i++)
  {
    OverlapResult overlapResult = doesRectCornerOverlapOtherRect(rect1Corners, i, rect2Corners);
    if (overlapResult.doesOverlap &&
      overlapResult.resolutionVector.length() < minOverlapResult.resolutionVector.length())
    {
      minOverlapResult = overlapResult;
    }
  }

  return minOverlapResult;
}

std::optional<Line> Geometry::getLineDefinedByTwoPoints(Vector p, Vector q)
{
  if (p.x == q.x)
    return std::nullopt;

  float angle = (q.y - p.y) / (q.x - p.x);
  return Line{
    angle,
    p.y - angle * p.x
  };
}

std::vector<std::optional<Line>> Geometry::getLinesDefinedBySidesThatContainsPoint(CornerInfo cornerInfo)
{
  std::vector<std::optional<Line>> res{};

  if (cornerInfo.isCorner)
  {
    res.push_back(getLineDefinedByTwoPoints(cornerInfo.prevPoint, cornerInfo.point));
  }
  res.push_back(getLineDefinedByTwoPoints(cornerInfo.point, cornerInfo.nextPoint));

  return res;
}

std::array<Vector, 2>
Geometry::getIntersectionsOfLineAndEllipse(std::optional<Line> lineOpt, Vector pointOnLine,
                                           Vector ellipCenter, EllipseAxes axes)
{
  Vector intersect1, intersect2;
  if (lineOpt.has_value())
  {
    Line line = lineOpt.value();

    float sl = line.slope;
    float yI = sl * ellipCenter.x + line.yIntercept - ellipCenter.y;
    yI = std::abs(yI) < TREAT_AS_GOING_THROUGH_ELLIPSE_CENTER ? 0.0f : yI;
    float j = axes.sMajor;
    float m = axes.sMinor;

    float x1, x2;
    if (sl == 0.0f)
    {
      x1 = j / m * sqrt(m * m - yI * yI);
    }
    else
    {
      float a = m * m + sl * sl * j * j;
      float b = 2 * j * j * sl * yI;
      float c = j * j * b * b - j * j * m * m;
      float delta = b * b - 4 * a * c;
      if (delta <= 0)
      {
        // TODO: Sometimes is thrown wtffff
        throw std::runtime_error("Expected a solution but none was found.");
      }

      x1 = (-b + sqrt(delta)) / (2 * a);
    }

    intersect1 = Vector{
      x1,
      sl * x1 + yI
    } + ellipCenter;

    x2 = -x1;
    intersect2 = Vector{x2, sl * x2 + yI} + ellipCenter;
  }
  else
  {
    float y0;
    if (pointOnLine == ellipCenter)
    {
      y0 = ellipCenter.y + axes.sMinor;
    }
    else
    {
      y0 = axes.sMinor * sqrt(1 - pow(pointOnLine.x / axes.sMajor, 2));
    }
    intersect1 = Vector{pointOnLine.x, y0} + ellipCenter;
    intersect2 = Vector{pointOnLine.x, -y0} + ellipCenter;
  }

  return std::array{intersect1, intersect2};
}

std::optional<Line> Geometry::getPerpendicularLineAtPoint(Vector point, std::optional<Line> lineOpt)
{
  if (!lineOpt.has_value())
    return Line{0.0f, point.y};

  if (lineOpt->slope == 0.0f)
    return std::nullopt;

  Line line = lineOpt.value();
  return Line{-line.slope, point.y + line.slope * point.x};
}

Vector Geometry::getClosestIntersectionToPoint(std::array<Vector, 2> intersections, Vector point)
{
  if ((intersections[0] - point).length() < (intersections[1] - point).length())
    return intersections[0];

  return intersections[1];
}

CornerInfo Geometry::isCorner(Vector point, RectangleCorners rect)
{
  int howManySidesContainPoint = 0;
  CornerInfo res{};
  for (int i = 0; i < RECTANGLE_CORNERS_COUNT; i++)
  {
    Vector sideStart = rect[i];
    Vector sideEnd = rect[(i + 1) % 4];

    if (point.isOnSegment(sideStart, sideEnd))
    {
      howManySidesContainPoint++;
      res = CornerInfo{false, sideStart, sideStart, sideEnd};
      if (howManySidesContainPoint == 2)
      {
        res = CornerInfo{true, rect[(i - 1) % 4], sideStart, sideEnd};
        return res;
      }
    }
  }

  return res;
}