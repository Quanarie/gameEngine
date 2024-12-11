#include <array>

#include "component/collider/rectangle/rectangle_colider_component.h"
#include "component/collider/collision_resolver.h"
#include "component/collider/rectangle/rectangle_corners.h"

bool RectangleColliderComponent::detect(const ColliderComponent& other,
                                        TransformComponent& transformThis,
                                        TransformComponent& transformOther) const {
  return other.detectWith(*this, transformOther, transformThis);
}

bool RectangleColliderComponent::detectWith(const RectangleColliderComponent& rect,
                                            TransformComponent& transformThis,
                                            TransformComponent& transformOther) const {
  return CollisionResolver::resolve(rect, transformOther, *this, transformThis);
}

bool RectangleColliderComponent::detectWith(const EllipseColliderComponent& ellipse,
                                            TransformComponent& transformThis,
                                            TransformComponent& transformOther) const {
  return CollisionResolver::resolve(ellipse, transformOther, *this, transformThis);
}

std::pair<Vector, Vector> RectangleColliderComponent::getTransformedDefiningCorners(Vector relativeTo) const {
  return {this->leftDown + relativeTo, this->rightUp + relativeTo};
}

RectangleCorners RectangleColliderComponent::getTransformedCorners(Vector relativeTo) const {
  return RectangleCorners{
    this->leftDown + relativeTo,
    Vector{this->leftDown.x, this->rightUp.y} + relativeTo,
    this->rightUp + relativeTo,
    Vector{this->rightUp.x, this->leftDown.y} + relativeTo
  };
}
