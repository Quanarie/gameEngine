#include <array>

#include "component/collider/rectangle_colider_component.h"
#include "component/collider/collision_resolver.h"

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

std::array<Point, 4> RectangleColliderComponent::getTransformedCorners(Point relativeTo) const {
  return {
    this->leftDown + relativeTo,
    Point{this->leftDown.x, this->rightUp.y} + relativeTo,
    this->rightUp + relativeTo,
    Point{this->rightUp.x, this->leftDown.y} + relativeTo
  };
}
