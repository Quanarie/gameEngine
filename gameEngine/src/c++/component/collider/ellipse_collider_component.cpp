#include <component/transform_component.h>

#include "static/collision_resolver.h"
#include "component/collider/ellipse/ellipse_colider_component.h"

bool EllipseColliderComponent::resolve(const ColliderComponent& other) const {
  return other.resolveWith(*this);
}

bool EllipseColliderComponent::resolveWith(const RectangleColliderComponent& rect) const {
  return CollisionResolver::resolve(*this, rect);
}

bool EllipseColliderComponent::resolveWith(const EllipseColliderComponent& ellipse) const {
  return CollisionResolver::resolve(ellipse, *this);
}

Vector EllipseColliderComponent::getTransformedCenter() const {
  return this->center + this->transform->pos;
}

Vector EllipseColliderComponent::getScaledAxes() const {
  return Vector{
    this->axes.x * this->transform->scale.x,
    this->axes.y * this->transform->scale.y
  };
}
