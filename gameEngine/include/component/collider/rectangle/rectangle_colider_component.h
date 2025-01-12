#ifndef RECTANGLE_COLLIDER_COMPONENT_H
#define RECTANGLE_COLLIDER_COMPONENT_H

#include <entity.h>

#include "component/collider/collider_component.h"
#include "component/render/rectangle_render_component.h"
#include "util/vector.h"

struct RectangleCorners;
class CollisionResolver;

// Possible take out shape related things and use them in both renderers and colliders with the same shape
class RectangleColliderComponent : public ColliderComponent {
public:
  Vector leftDown, rightUp;

  RectangleColliderComponent(Vector ld, Vector ru)
    : leftDown(ld), rightUp(ru) {
    colliderBoundsRenderComponent = new RectangleRenderComponent(ld, ru);
  }

  ~RectangleColliderComponent() override {
    delete colliderBoundsRenderComponent;
  }

  bool resolve(const ColliderComponent& other) const override;
  bool resolveWith(const RectangleColliderComponent& rect) const override;
  bool resolveWith(const EllipseColliderComponent& ellipse) const override;

  RectangleCorners getTransformedCorners() const;
};

#endif // RECTANGLE_COLLIDER_COMPONENT_H
