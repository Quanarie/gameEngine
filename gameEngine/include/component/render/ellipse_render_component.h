#ifndef ELLIPSE_RENDER_COMPONENT_H
#define ELLIPSE_RENDER_COMPONENT_H

#include "component/collider/ellipse/ellipse_axes.h"
#include "component/render/render_component.h"
#include "util/vector.h"

class TransformComponent;

class EllipseRenderComponent : public RenderComponent {
public:
  Vector center;
  EllipseAxes axes;

  EllipseRenderComponent(Vector c, EllipseAxes r)
    : center(c), axes(r) {}

  void render(SDL_Renderer* renderer) override;
};

#endif // ELLIPSE_RENDER_COMPONENT_H
