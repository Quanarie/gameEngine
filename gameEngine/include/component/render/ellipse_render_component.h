#ifndef ELLIPSE_RENDER_COMPONENT_H
#define ELLIPSE_RENDER_COMPONENT_H

#include "util/vector.h"
#include "component/render/render_component.h"

class TransformComponent;

class EllipseRenderComponent : public RenderComponent {
public:
  Vector center;
  Vector axes;

  EllipseRenderComponent(Vector c, Vector r)
    : center(c), axes(r) {}

  void render(SDL_Renderer* renderer) override;
};

#endif // ELLIPSE_RENDER_COMPONENT_H
