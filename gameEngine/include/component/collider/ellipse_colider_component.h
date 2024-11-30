#ifndef ELLIPSE_COLLIDER_COMPONENT_H
#define ELLIPSE_COLLIDER_COMPONENT_H

#include "collider_component.h"
#include "math/point.h"

class EllipseColliderComponent : public ColliderComponent {
public:
  Point center;
  Point radiuses;

  EllipseColliderComponent(Point c, Point r)
    : center(c), radiuses(r) {}

  bool detect(const ColliderComponent& other,
              const TransformComponent& transformThis,
              const TransformComponent& transformOther) const override;

  bool detectWith(const EllipseColliderComponent& ellipse,
                  const TransformComponent& transformThis,
                  const TransformComponent& transformOther) const override;

  bool detectWith(const RectangleColliderComponent& rect,
                  const TransformComponent& transformThis,
                  const TransformComponent& transformOther) const override;
};

#endif // ELLIPSE_COLLIDER_COMPONENT_H
