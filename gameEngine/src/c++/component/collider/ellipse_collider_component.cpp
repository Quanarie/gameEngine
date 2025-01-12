#include <component/transform_component.h>

#include "static/collision_resolver.h"
#include "component/collider/ellipse/ellipse_colider_component.h"

bool EllipseColliderComponent::resolve(const ColliderComponent& other,
                                      TransformComponent& transformThis,
                                      TransformComponent& transformOther) const {
  return other.resolveWith(*this, transformOther, transformThis);
}

bool EllipseColliderComponent::resolveWith(const RectangleColliderComponent& rect,
                                          TransformComponent& transformThis,
                                          TransformComponent& transformOther) const {
  return CollisionResolver::resolve(*this, transformThis, rect, transformOther);
}

bool EllipseColliderComponent::resolveWith(const EllipseColliderComponent& ellipse,
                                          TransformComponent& transformThis,
                                          TransformComponent& transformOther) const {
  return CollisionResolver::resolve(ellipse, transformOther, *this, transformThis);
}

Vector EllipseColliderComponent::getTransformedCenter(Vector pos) const {
  return this->center + pos;
}

Vector EllipseColliderComponent::getScaledAxes() const {
  return Vector{
    this->axes.x * this->transform->scale.x,
    this->axes.y * this->transform->scale.y
  };
}
