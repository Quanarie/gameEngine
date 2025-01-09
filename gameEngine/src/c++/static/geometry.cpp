#include "static/geometry.h"

#include <limits>
#include <optional>
#include <vector>
#include <static/inputs.h>

#include "util/vector.h"
#include "component/collider/ellipse/ellipse_axes.h"
#include "component/collider/rectangle/rectangle_corners.h"

#define RECTANGLE_CORNERS_COUNT 4
#define MAX_SIDES_CONTAINING_SAME_POINT 2
#define TREAT_AS_GOING_THROUGH_ELLIPSE_CENTER 0.25f

void projectPolygonOntoAxis(std::vector<Vector>& pol,
                              Vector& axis,
                              float& min,
                              float& max)
{
  min = max = pol[0].dot(axis);
  for (auto& vertex : pol) {
    float projection = vertex.dot(axis);
    if (projection < min) min = projection;
    if (projection > max) max = projection;
  }
}

float Geometry::calculatePenetration(std::vector<Vector>& pol1,
                           Vector pol1Center,
                           std::vector<Vector>& pol2,
                           Vector pol2Center,
                           Vector& collisionNormal)
{
  float minPenetration = std::numeric_limits<float>::max();
  Vector bestAxis;

  std::vector<Vector> axes;

  for (size_t i = 0; i < pol1.size(); ++i) {
    Vector edge = pol1[(i + 1) % pol1.size()] - pol1[i];
    Vector axis = Vector{-edge.y, edge.x}.normalized();
    axes.push_back(axis);
  }

  for (size_t i = 0; i < pol2.size(); ++i) {
    Vector edge = pol2[(i + 1) % pol2.size()] - pol2[i];
    Vector axis = Vector{-edge.y, edge.x}.normalized();
    axes.push_back(axis);
  }

  for (auto& axis : axes)
  {
    float min1, max1, min2, max2;

    projectPolygonOntoAxis(pol1, axis, min1, max1);
    projectPolygonOntoAxis(pol2, axis, min2, max2);

    float overlap = std::min(max1, max2) - std::max(min1, min2);

    if (overlap <= 0) { return 0.0f; }

    if (overlap < minPenetration)
    {
      minPenetration = overlap;
      bestAxis = axis;
    }
  }

  Vector centerToCenter = pol1Center - pol2Center;
  if (centerToCenter.dot(bestAxis) < 0) { bestAxis = Vector{0.0f, 0.0f} - bestAxis; }

  collisionNormal = bestAxis;
  return minPenetration;
}

std::optional<Vector> Geometry::findLinesIntersectionPoint(Vector a1, Vector b1, Vector a2, Vector b2)
{
  float s1_x, s1_y, s2_x, s2_y;
  s1_x = b1.x - a1.x;
  s1_y = b1.y - a1.y;
  s2_x = b2.x - a2.x;
  s2_y = b2.y - a2.y;

  float s, t;
  s = (-s1_y * (a1.x - a2.x) + s1_x * (a1.y - a2.y)) / (-s2_x * s1_y + s1_x * s2_y);
  t = (s2_x * (a1.y - a2.y) - s2_y * (a1.x - a2.x)) / (-s2_x * s1_y + s1_x * s2_y);

  if (s >= 0 && s <= 1 && t >= 0 && t <= 1) { return Vector{a1.x + (t * s1_x), a1.y + (t * s1_y)}; }

  return std::nullopt;
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

  if (cornerInfo.isCorner) { res.push_back(getLineDefinedByTwoPoints(cornerInfo.prevPoint, cornerInfo.point)); }
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
    if (sl == 0.0f) { x1 = j / m * sqrt(m * m - yI * yI); }
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
    if (pointOnLine == ellipCenter) { y0 = ellipCenter.y + axes.sMinor; }
    else { y0 = axes.sMinor * sqrt(1 - pow(pointOnLine.x / axes.sMajor, 2)); }
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
    Vector sideEnd = rect[(i + 1) % RECTANGLE_CORNERS_COUNT];

    if (point.isOnSegment(sideStart, sideEnd))
    {
      howManySidesContainPoint++;
      res = CornerInfo{false, sideStart, sideStart, sideEnd};
      if (howManySidesContainPoint == 2)
      {
        res = CornerInfo{true, rect[(i - 1) % RECTANGLE_CORNERS_COUNT], sideStart, sideEnd};
        return res;
      }
    }
  }

  return res;
}
