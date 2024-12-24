#include <array>
#include <vector>
#include <__algorithm/clamp.h>

#include "static/geometry.h"
#include "static/collision_resolver.h"
#include "static/coordinates_converter.h"
#include "component/transform_component.h"
#include "component/collider/rectangle/rectangle_corners.h"
#include "component/collider/ellipse/ellipse_colider_component.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

void doResolve(const ColliderComponent& coll1,
               TransformComponent& trans1,
               const ColliderComponent& coll2,
               TransformComponent& trans2,
               Vector resolutionVector)
{
  bool bothStatic = coll1.isStatic && coll2.isStatic;
  bool bothNotStatic = !coll1.isStatic && !coll2.isStatic;
  // TODO: for now if both static then they move each other normally
  if (bothStatic || bothNotStatic)
  {
    trans1.pos = trans1.pos + resolutionVector / 2;
    trans2.pos = trans2.pos - resolutionVector / 2;
  }
  else
  {
    trans1.pos = trans1.pos + resolutionVector * (coll1.isStatic && !coll2.isStatic ? 0 : 1);
    trans2.pos = trans2.pos - resolutionVector * (coll2.isStatic && !coll1.isStatic ? 0 : 1);
  }
}

bool CollisionResolver::resolve(const RectangleColliderComponent& rect1,
                                TransformComponent& trans1,
                                const RectangleColliderComponent& rect2,
                                TransformComponent& trans2)
{
  auto rect1Corners = rect1.getTransformedCorners();
  auto rect2Corners = rect2.getTransformedCorners();

  OverlapResult res = Geometry::anyCornerOfRect1InsideRect2(rect1Corners, rect2Corners);
  // We need to check if any corner of rect1 is in rect2 or vice versa, cuz rectangles can be rotated (in future)
  if (!res.doesOverlap)
  {
    res = Geometry::anyCornerOfRect1InsideRect2(rect2Corners, rect1Corners);
    if (res.doesOverlap) { res.resolutionVector = Vector{0.0f, 0.0f} - res.resolutionVector; }
  }

  if (!res.doesOverlap || res.resolutionVector == Vector{0.0f, 0.0f}) { return false; }

  doResolve(rect1, trans1, rect2, trans2, res.resolutionVector);
  return true;
}

bool CollisionResolver::resolve(const EllipseColliderComponent& ellip,
                                TransformComponent& transEllip,
                                const RectangleColliderComponent& rect,
                                TransformComponent& transRect)
{
  Vector ellipCenter = ellip.getTransformedCenter(transEllip.pos);
  auto rectCorners = rect.getTransformedCorners();

  auto closestPointToEllipInRect = Vector{
    std::clamp(ellipCenter.x, rectCorners.ld.x, rectCorners.ru.x),
    std::clamp(ellipCenter.y, rectCorners.ld.y, rectCorners.ru.y)
  };

  auto relativeToEllip = closestPointToEllipInRect - ellipCenter;

  if (relativeToEllip.x * relativeToEllip.x / (ellip.getScaledAxes().sMajor * ellip.getScaledAxes().sMajor) +
    relativeToEllip.y * relativeToEllip.y / (ellip.getScaledAxes().sMinor * ellip.getScaledAxes().sMinor) >= 1)
    return false;

  std::vector<std::optional<Line>> linesContainingClosestPoint = Geometry::getLinesDefinedBySidesThatContainsPoint(
    Geometry::isCorner(closestPointToEllipInRect, rectCorners));

  Vector resolutionVector{0.0f, 0.0f};
  float weightSum = 0.0f;

  // TODO: Try to take two point of intersection, get perpen in middle of it as resolutionVector
  // That would eliminate the need for this cycle and weights
  for (auto line : linesContainingClosestPoint)
  {
    std::optional<Line> perperndicularToLineContClosestPoint = Geometry::getPerpendicularLineAtPoint(
      closestPointToEllipInRect, line);

    std::array<Vector, 2> intersections = Geometry::getIntersectionsOfLineAndEllipse(
      perperndicularToLineContClosestPoint,
      relativeToEllip,
      ellipCenter,
      ellip.getScaledAxes()
    );

    Vector closestIntersection = Geometry::getClosestIntersectionToPoint(intersections, closestPointToEllipInRect);
    Vector currentResolutionVector = closestPointToEllipInRect - closestIntersection;

    float weight = 1.0f / (1.0f + std::abs(currentResolutionVector.length() - resolutionVector.length()));
    resolutionVector = resolutionVector + (currentResolutionVector * weight);
    weightSum += weight;
  }

  if (weightSum > 0.0f) { resolutionVector = resolutionVector * (1.0f / weightSum); }

  doResolve(ellip, transEllip, rect, transRect, resolutionVector);
  return true;
}

bool CollisionResolver::resolve(const EllipseColliderComponent& ell1,
                                TransformComponent& trans1,
                                const EllipseColliderComponent& ell2,
                                TransformComponent& trans2)
{
  Vector ell1Center = ell1.getTransformedCenter(trans1.pos);
  Vector ell2Center = ell2.getTransformedCenter(trans2.pos);

  // Treating 1 center as a point we should check to lie within a "combined" ellipse
  // Intuitively: we can shrink first ellipse and expand second as much till second becomes just a point
  // Curvature of ellipses are same so shrinking and expanding is equivalent
  Vector center1RelatTo2 = Vector{
    ell1Center.x - ell2Center.x,
    ell1Center.y - ell2Center.y
  };

  EllipseAxes combinedAxes = EllipseAxes{
    ell1.getScaledAxes().sMajor + ell2.getScaledAxes().sMajor,
    ell1.getScaledAxes().sMinor + ell2.getScaledAxes().sMinor
  };

  if (center1RelatTo2.x * center1RelatTo2.x / (combinedAxes.sMajor * combinedAxes.sMajor) +
    center1RelatTo2.y * center1RelatTo2.y / (combinedAxes.sMinor * combinedAxes.sMinor) > 1)
    return false;

  // Weird pseudo algorithm given to me by god that doesnt really work well with ellipses that are not circles
  std::array<Vector, 2> intersections = Geometry::getIntersectionsOfLineAndEllipse(
    Geometry::getLineDefinedByTwoPoints(ell1Center, ell2Center),
    ell1Center,
    ell2Center,
    combinedAxes
  );

  Vector closestIntersection = Geometry::getClosestIntersectionToPoint(intersections, ell1Center);
  Vector resolutionVector = closestIntersection - ell1Center;

  doResolve(ell1, trans1, ell2, trans2, resolutionVector);
  return true;
}
