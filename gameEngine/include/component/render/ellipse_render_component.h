#ifndef ELLIPSE_RENDER_COMPONENT_H
#define ELLIPSE_RENDER_COMPONENT_H

#include "component/collider/ellipse/ellipse_axes.h"
#include "component/render/render_component.h"
#include "math/point.h"

class TransformComponent;

class EllipseRenderComponent : public RenderComponent {
public:
  Point center;
  EllipseAxes axes;

  EllipseRenderComponent(Point c, EllipseAxes r)
    : center(c), axes(r) {}

  void render(SDL_Renderer* renderer, TransformComponent* transform) override;
};

#endif // ELLIPSE_RENDER_COMPONENT_H
