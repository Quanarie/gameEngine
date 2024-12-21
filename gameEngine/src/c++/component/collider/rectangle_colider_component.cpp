#include "static/collision_resolver.h"
#include "component/collider/rectangle/rectangle_corners.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

#include <component/transform_component.h>

bool RectangleColliderComponent::resolve(const ColliderComponent& other,
                                        TransformComponent& transformThis,
                                        TransformComponent& transformOther) const {
  return other.resolveWith(*this, transformOther, transformThis);
}

bool RectangleColliderComponent::resolveWith(const RectangleColliderComponent& rect,
                                            TransformComponent& transformThis,
                                            TransformComponent& transformOther) const {
  return CollisionResolver::resolve(rect, transformOther, *this, transformThis);
}

bool RectangleColliderComponent::resolveWith(const EllipseColliderComponent& ellipse,
                                            TransformComponent& transformThis,
                                            TransformComponent& transformOther) const {
  return CollisionResolver::resolve(ellipse, transformOther, *this, transformThis);
}

RectangleCorners RectangleColliderComponent::getTransformedCorners(Vector relativeToSdlCoords) const {
  Vector scaledLD = this->leftDown * this->transform->scale;
  Vector scaledRU = this->rightUp * this->transform->scale;
  return RectangleCorners{
    scaledLD + relativeToSdlCoords,
    Vector{scaledLD.x, scaledRU.y} + relativeToSdlCoords,
    scaledRU + relativeToSdlCoords,
    Vector{scaledRU.x, scaledLD.y} + relativeToSdlCoords
  };
}
