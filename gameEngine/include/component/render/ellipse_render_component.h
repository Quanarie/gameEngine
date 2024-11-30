#ifndef ELLIPSE_RENDER_COMPONENT_H
#define ELLIPSE_RENDER_COMPONENT_H

#include "component/render/render_component.h"
#include "math/point.h"

class TransformComponent;

class EllipseRenderComponent : public RenderComponent {
public:
  Point center;
  Point radiuses;

  EllipseRenderComponent(Point c, Point r)
    : center(c), radiuses(r) {}

  void render(SDL_Renderer *renderer,
                TransformComponent *transform) override;
};

#endif // ELLIPSE_RENDER_COMPONENT_H
