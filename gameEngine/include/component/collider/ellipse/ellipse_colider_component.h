#ifndef ELLIPSE_COLLIDER_COMPONENT_H
#define ELLIPSE_COLLIDER_COMPONENT_H

#include "ellipse_axes.h"
#include "component/collider/collider_component.h"
#include "component/render/ellipse_render_component.h"
#include "util/vector.h"

class EllipseColliderComponent : public ColliderComponent {
public:
  EllipseColliderComponent(Vector c, EllipseAxes r)
    : center(c), axes(r) {
    colliderBoundsRenderComponent = new EllipseRenderComponent(c, r);
  }

  ~EllipseColliderComponent() override {
    delete colliderBoundsRenderComponent;
  }

  bool resolve(const ColliderComponent& other,
              TransformComponent& transformThis,
              TransformComponent& transformOther) const override;

  bool resolveWith(const EllipseColliderComponent& ellipse,
                  TransformComponent& transformThis,
                  TransformComponent& transformOther) const override;

  bool resolveWith(const RectangleColliderComponent& rect,
                  TransformComponent& transformThis,
                  TransformComponent& transformOther) const override;

  Vector getTransformedCenter(Vector relativeTo) const;
  EllipseAxes getScaledAxes() const;

private:
  Vector center;
  EllipseAxes axes;
};

#endif // ELLIPSE_COLLIDER_COMPONENT_H
