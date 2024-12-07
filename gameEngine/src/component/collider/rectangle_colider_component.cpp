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

std::pair<Point, Point> RectangleColliderComponent::getTransformedDefiningCorners(Point relativeTo) const {
  return {this->leftDown + relativeTo, this->rightUp + relativeTo};
}

RectangleCorners RectangleColliderComponent::getTransformedCorners(Point relativeTo) const {
  return RectangleCorners{
    this->leftDown + relativeTo,
    Point{this->leftDown.x, this->rightUp.y} + relativeTo,
    this->rightUp + relativeTo,
    Point{this->rightUp.x, this->leftDown.y} + relativeTo
  };
}
