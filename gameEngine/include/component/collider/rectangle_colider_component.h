#ifndef RECTANGLE_COLLIDER_COMPONENT_H
#define RECTANGLE_COLLIDER_COMPONENT_H

#include <tuple>

#include "collider_component.h"
#include "component/render/rectangle_render_component.h"
#include "math/point.h"

class CollisionDetector;

// Possible take out shape related things and use them in both renderers and colliders with the same shape
class RectangleColliderComponent : public ColliderComponent {
public:
  Point leftDown, rightUp;

  RectangleColliderComponent(Point ld, Point ru)
    : leftDown(ld), rightUp(ru) {
    colliderBoundsRenderComponent = new RectangleRenderComponent(ld, ru);
  }

  ~RectangleColliderComponent() override {
    delete colliderBoundsRenderComponent;
  }

  bool detect(const ColliderComponent& other,
              const TransformComponent& transformThis,
              const TransformComponent& transformOther) const override;

  bool detectWith(const RectangleColliderComponent& rect,
                  const TransformComponent& transformThis,
                  const TransformComponent& transformOther) const override;

  bool detectWith(const EllipseColliderComponent& ellipse,
                  const TransformComponent& transformThis,
                  const TransformComponent& transformOther) const override;

  std::pair<Point, Point> getTransformedDefiningCorners(Point relativeTo) const;
};

#endif // RECTANGLE_COLLIDER_COMPONENT_H
