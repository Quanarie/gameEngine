#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <optional>

#include "util/vector.h"

struct Vector;
struct RectangleCorners;

struct OverlapResult
{
  bool doesOverlap;
  Vector resolutionVector;
};

struct Line
{
  float slope;
  float yIntercept;
};

struct CornerInfo
{
  bool isCorner = false;
  Vector prevPoint;
  Vector point;
  Vector nextPoint;
};

class Geometry
{
public:
  static float calculatePenetration(std::vector<Vector>& pol1, Vector pol1Center, std::vector<Vector>& pol2,
                                    Vector pol2Center, Vector& collisionNormal);
  static std::optional<Line> getLineDefinedByTwoPoints(Vector p, Vector q);

  static std::array<Vector, 2>
  getIntersectionsOfLineAndEllipse(std::optional<Line> lineOpt, Vector pointOnLine, Vector ellipCenter,
                                   Vector axes);
  static std::optional<Line> getPerpendicularLineAtPoint(Vector point, std::optional<Line> lineOpt);

  static std::vector<std::optional<Line>> getLinesDefinedBySidesThatContainsPoint(CornerInfo cornerInfo);

  static CornerInfo isCorner(Vector point, RectangleCorners rect);

  static Vector getClosestIntersectionToPoint(std::array<Vector, 2> intersections, Vector point);

  static OverlapResult anyCornerOfRect1InsideRect2(const RectangleCorners& rect1Corners,
                                                   const RectangleCorners& rect2Corners);

  static std::optional<Vector> findLinesIntersectionPoint(Vector a1, Vector b1, Vector a2, Vector b2);

  // TODO: methods for developers, fe: getClosestPointFromArrayToPassedAsArgumentPoint fuck yeahhhhh
};

#endif // GEOMETRY_H
