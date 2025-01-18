#ifndef ELLIPSE_COLLIDER_COMPONENT_H
#define ELLIPSE_COLLIDER_COMPONENT_H

#include "util/vector.h"
#include "component/collider/collider_component.h"
#include "component/render/ellipse_render_component.h"

class EllipseColliderComponent : public ColliderComponent {
public:
  EllipseColliderComponent(Vector c, Vector r)
    : center(c), axes(r) {
    colliderBoundsRenderComponent = new EllipseRenderComponent(c, r);
  }

  ~EllipseColliderComponent() override {
    delete colliderBoundsRenderComponent;
  }

  bool resolve(const ColliderComponent& other) const override;
  bool resolveWith(const EllipseColliderComponent& ellipse) const override;
  bool resolveWith(const RectangleColliderComponent& rect) const override;

  Vector getTransformedCenter() const;
  Vector getScaledAxes() const;

private:
  Vector center;
  Vector axes;
};

#endif // ELLIPSE_COLLIDER_COMPONENT_H
