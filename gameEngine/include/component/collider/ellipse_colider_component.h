#ifndef ELLIPSE_COLLIDER_COMPONENT_H
#define ELLIPSE_COLLIDER_COMPONENT_H

#include "collider_component.h"
#include "component/render/ellipse_render_component.h"
#include "math/point.h"

class EllipseColliderComponent : public ColliderComponent {
public:
  Point center;
  Point radiuses;

  EllipseColliderComponent(Point c, Point r)
    : center(c), radiuses(r) {
    colliderBoundsRenderComponent = new EllipseRenderComponent(c, r);
  }

  ~EllipseColliderComponent() override {
    delete colliderBoundsRenderComponent;
  }

  bool detect(const ColliderComponent& other,
              TransformComponent& transformThis,
              TransformComponent& transformOther) const override;

  bool detectWith(const EllipseColliderComponent& ellipse,
                  TransformComponent& transformThis,
                  TransformComponent& transformOther) const override;

  bool detectWith(const RectangleColliderComponent& rect,
                  TransformComponent& transformThis,
                  TransformComponent& transformOther) const override;

  Point getTransformedCenter(Point relativeTo) const;
};

#endif // ELLIPSE_COLLIDER_COMPONENT_H
