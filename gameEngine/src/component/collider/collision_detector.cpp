#include "component/collider/collision_detector.h"

#include <__algorithm/clamp.h>

#include "component/transform_component.h"
#include "component/collider/ellipse_colider_component.h"
#include "component/collider/rectangle_colider_component.h"
#include "math/point.h"

// Create tests for this pls
bool CollisionDetector::detect(const RectangleColliderComponent& rect1,
                               const TransformComponent& trans1,
                               const RectangleColliderComponent& rect2,
                               const TransformComponent& trans2) {
  auto [rect1LD, rect1RU] = rect1.getTransformedDefiningCorners(trans1.position);
  auto [rect2LD, rect2RU] = rect2.getTransformedDefiningCorners(trans2.position);

  return !(rect1LD.x > rect2RU.x || rect1RU.x < rect2LD.x ||
    rect1LD.y > rect2RU.y || rect1RU.y < rect2LD.y);
}

bool CollisionDetector::detect(const EllipseColliderComponent& ellip,
                               const TransformComponent& transEllip,
                               const RectangleColliderComponent& rect,
                               const TransformComponent& transRect) {
  Point ellipCenter = ellip.getTransformedCenter(transEllip.position);
  auto [rect1LD, rect1RU] = rect.getTransformedDefiningCorners(transRect.position);

  auto closestPointToEllipInRect = Point{
    std::clamp(ellipCenter.x, rect1LD.x, rect1RU.x),
    std::clamp(ellipCenter.y, rect1LD.y, rect1RU.y)
  };

  auto relativeToEllip = Point{
    ellipCenter.x - closestPointToEllipInRect.x,
    ellipCenter.y - closestPointToEllipInRect.y
  };

  return (relativeToEllip.x * relativeToEllip.x) / (ellip.radiuses.x * ellip.radiuses.x) +
    (relativeToEllip.y * relativeToEllip.y) / (ellip.radiuses.y * ellip.radiuses.y) <= 1;
}

bool CollisionDetector::detect(const EllipseColliderComponent& ell1,
                               const TransformComponent& trans1,
                               const EllipseColliderComponent& ell2,
                               const TransformComponent& trans2) {
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
    ell1.radiuses.x + ell2.radiuses.x,
    ell1.radiuses.y + ell2.radiuses.y
  };

  return center2RelatTo1.x * center2RelatTo1.x / (combinedRads.x * combinedRads.x) +
    center2RelatTo1.y * center2RelatTo1.y / (combinedRads.y * combinedRads.y) <= 1;
}
