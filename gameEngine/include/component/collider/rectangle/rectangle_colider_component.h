#ifndef RECTANGLE_COLLIDER_COMPONENT_H
#define RECTANGLE_COLLIDER_COMPONENT_H

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

  bool detect(const ColliderComponent& other,
              TransformComponent& transformThis,
              TransformComponent& transformOther) const override;

  bool detectWith(const RectangleColliderComponent& rect,
                  TransformComponent& transformThis,
                  TransformComponent& transformOther) const override;

  bool detectWith(const EllipseColliderComponent& ellipse,
                  TransformComponent& transformThis,
                  TransformComponent& transformOther) const override;

  RectangleCorners getTransformedCorners(Vector relativeToSdlCoords) const;
};

#endif // RECTANGLE_COLLIDER_COMPONENT_H
