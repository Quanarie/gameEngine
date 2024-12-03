#include "component/collider/collision_detector.h"
#include "component/collider/ellipse_colider_component.h"

bool EllipseColliderComponent::detect(const ColliderComponent& other,
                                      const TransformComponent& transformThis,
                                      const TransformComponent& transformOther) const {
  return other.detectWith(*this, transformOther, transformThis);
}

bool EllipseColliderComponent::detectWith(const RectangleColliderComponent& rect,
                                          const TransformComponent& transformThis,
                                          const TransformComponent& transformOther) const {
  return CollisionDetector::detect(*this, transformThis, rect, transformOther);
}

bool EllipseColliderComponent::detectWith(const EllipseColliderComponent& ellipse,
                                          const TransformComponent& transformThis,
                                          const TransformComponent& transformOther) const {
  return CollisionDetector::detect(ellipse, transformOther, *this, transformThis);
}

Point EllipseColliderComponent::getTransformedCenter(Point relativeTo) const {
  return this->center + relativeTo;
}