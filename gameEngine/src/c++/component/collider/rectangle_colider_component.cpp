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
  Vector invertedLD = this->leftDown * Vector{1.0f, -1.0f};
  Vector invertedRU = this->rightUp * Vector{1.0f, -1.0f};
  return RectangleCorners{
    invertedLD + relativeToSdlCoords,
    Vector{invertedLD.x, invertedRU.y} + relativeToSdlCoords,
    invertedRU + relativeToSdlCoords,
    Vector{invertedRU.x, invertedLD.y} + relativeToSdlCoords
  };
}
