#include "component/collider/rectangle_colider_component.h"
#include "component/collider/collision_detector.h"

bool RectangleColliderComponent::detect(
  const ColliderComponent& other,
  const TransformComponent& transformThis,
  const TransformComponent& transformOther) const {
  return other.detectWith(*this, transformOther, transformThis);
}

bool RectangleColliderComponent::detectWith(
  const RectangleColliderComponent& rect,
  const TransformComponent& transformThis,
  const TransformComponent& transformOther) const {
  return CollisionDetector::detect(rect, transformOther, *this, transformThis);
}
