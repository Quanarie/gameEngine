#include <array>
#include <vector>
#include <__algorithm/clamp.h>

#include "util/geometry.h"
#include "static/collision_resolver.h"

#include "static/coordinates_converter.h"
#include "component/transform_component.h"
#include "component/collider/rectangle/rectangle_corners.h"
#include "component/collider/ellipse/ellipse_colider_component.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

bool CollisionResolver::resolve(const RectangleColliderComponent& rect1,
                                TransformComponent& trans1,
                                const RectangleColliderComponent& rect2,
                                TransformComponent& trans2) {
  auto rect1Corners = rect1.getTransformedCorners(trans1.position);
  auto rect2Corners = rect2.getTransformedCorners(trans2.position);

  OverlapResult res = Geometry::anyCornerOfRect1InsideRect2(rect1Corners, rect2Corners);
  // We need to check if any corner of rect1 is in rect2 or vice versa, cuz rectangles can be rotated (in future)
  if (!res.doesOverlap) {
    res = Geometry::anyCornerOfRect1InsideRect2(rect2Corners, rect1Corners);
  }

  if (!res.doesOverlap || res.resolutionVector == Vector{0.0f, 0.0f}) {
    return false;
  }

  trans1.position = trans1.position + res.resolutionVector / 2;
  trans2.position = trans2.position - res.resolutionVector / 2;
  return true;
}

bool CollisionResolver::resolve(const EllipseColliderComponent& ellip,
                                TransformComponent& transEllip,
                                const RectangleColliderComponent& rect,
                                TransformComponent& transRect) {
  Vector ellipCenter = ellip.getTransformedCenter(transEllip.position);
  auto rectCorners = rect.getTransformedCorners(transRect.position);

  auto closestPointToEllipInRect = Vector{
    std::clamp(ellipCenter.x, rectCorners.ld.x, rectCorners.ru.x),
    std::clamp(ellipCenter.y, rectCorners.ld.y, rectCorners.ru.y)
  };

  auto relativeToEllip = closestPointToEllipInRect - ellipCenter;

  if (relativeToEllip.x * relativeToEllip.x / (ellip.axes.sMajor * ellip.axes.sMajor) +
    relativeToEllip.y * relativeToEllip.y / (ellip.axes.sMinor * ellip.axes.sMinor) >= 1)
    return false;

  std::vector<std::optional<Line>> linesContainingClosestPoint = Geometry::getLinesDefinedBySidesThatContainsPoint(
    Geometry::isCorner(closestPointToEllipInRect, rectCorners));

  Vector resolutionVector{0.0f, 0.0f};
  float weightSum = 0.0f;

  // TODO: Try to take two point of intersection, get perpen in middle of it as resolutionVector
  // That would eliminate the need for this cycle and weights
  for (auto line : linesContainingClosestPoint) {
    std::optional<Line> perperndicularToLineContClosestPoint = Geometry::getPerpendicularLineAtPoint(
      closestPointToEllipInRect, line);

    std::array<Vector, 2> intersections = Geometry::getIntersectionsOfLineAndEllipse(
      perperndicularToLineContClosestPoint,
      relativeToEllip,
      ellipCenter,
      ellip.axes
    );

    Vector closestIntersection = Geometry::getClosestIntersectionToPoint(intersections, closestPointToEllipInRect);
    Vector currentResolutionVector = closestPointToEllipInRect - closestIntersection;

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
  Vector ell1Center = ell1.center + trans1.position;
  Vector ell2Center = ell2.center + trans2.position;

  // Treating 1 center as a point we should check to lie within a "combined" ellipse
  // Intuitively: we can shrink first ellipse and expand second as much till second becomes just a point
  // Curvature of ellipses are same so shrinking and expanding is equivalent
  Vector center1RelatTo2 = Vector{
    ell1Center.x - ell2Center.x,
    ell1Center.y - ell2Center.y
  };

  EllipseAxes combinedAxes = EllipseAxes{
    ell1.axes.sMajor + ell2.axes.sMajor,
    ell1.axes.sMinor + ell2.axes.sMinor
  };

  if (center1RelatTo2.x * center1RelatTo2.x / (combinedAxes.sMajor * combinedAxes.sMajor) +
    center1RelatTo2.y * center1RelatTo2.y / (combinedAxes.sMinor * combinedAxes.sMinor) > 1)
    return false;

  // Weird pseudo algorithm given to me by god
  std::array<Vector, 2> intersections = Geometry::getIntersectionsOfLineAndEllipse(
    Geometry::getLineDefinedByTwoPoints(ell1Center, ell2Center),
    ell1Center,
    ell2Center,
    combinedAxes
  );

  Vector closestIntersection = Geometry::getClosestIntersectionToPoint(intersections, ell1Center);
  Vector resolutionVector = closestIntersection - ell1Center;
  trans1.position = trans1.position + resolutionVector / 2;
  trans2.position = trans2.position - resolutionVector / 2;

  return true;
}
