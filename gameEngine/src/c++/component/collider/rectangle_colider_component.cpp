#include "static/collision_resolver.h"
#include "component/collider/rectangle/rectangle_corners.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

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

RectangleCorners RectangleColliderComponent::getTransformedCorners(Vector relativeToSdlCoords) const {
  return RectangleCorners{
    this->leftDown + relativeToSdlCoords,
    Vector{this->leftDown.x, this->rightUp.y} + relativeToSdlCoords,
    this->rightUp + relativeToSdlCoords,
    Vector{this->rightUp.x, this->leftDown.y} + relativeToSdlCoords
  };
}
