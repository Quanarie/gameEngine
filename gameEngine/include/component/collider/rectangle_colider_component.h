#ifndef RECTANGLE_COLLIDER_COMPONENT_H
#define RECTANGLE_COLLIDER_COMPONENT_H

#include "collider_component.h"
#include "math/point.h"

class CollisionDetector;

class RectangleColliderComponent : public ColliderComponent {
public:
  Point leftDown, rightUp;

  RectangleColliderComponent(Point ld, Point ru)
    : leftDown(ld), rightUp(ru) {}

  bool detect(const ColliderComponent& other,
              const TransformComponent& transformThis,
              const TransformComponent& transformOther) const override;

  bool detectWith(const RectangleColliderComponent& rect,
                  const TransformComponent& transformThis,
                  const TransformComponent& transformOther) const override;

  bool detectWith(const EllipseColliderComponent& ellipse,
                  const TransformComponent& transformThis,
                  const TransformComponent& transformOther) const override;
};

#endif // RECTANGLE_COLLIDER_COMPONENT_H
