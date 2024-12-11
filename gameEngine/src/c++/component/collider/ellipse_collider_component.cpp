#include "component/collider/collision_resolver.h"
#include "component/collider/ellipse/ellipse_colider_component.h"

bool EllipseColliderComponent::detect(const ColliderComponent& other,
                                      TransformComponent& transformThis,
                                      TransformComponent& transformOther) const {
  return other.detectWith(*this, transformOther, transformThis);
}

bool EllipseColliderComponent::detectWith(const RectangleColliderComponent& rect,
                                          TransformComponent& transformThis,
                                          TransformComponent& transformOther) const {
  return CollisionResolver::resolve(*this, transformThis, rect, transformOther);
}

bool EllipseColliderComponent::detectWith(const EllipseColliderComponent& ellipse,
                                          TransformComponent& transformThis,
                                          TransformComponent& transformOther) const {
  return CollisionResolver::resolve(ellipse, transformOther, *this, transformThis);
}

Vector EllipseColliderComponent::getTransformedCenter(Vector relativeTo) const {
  return this->center + relativeTo;
}
