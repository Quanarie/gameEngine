#ifndef RECTANGLE_RENDER_COMPONENT_H
#define RECTANGLE_RENDER_COMPONENT_H

#include "render_component.h"
#include "component/transform_component.h"

class RectangleRenderComponent : public RenderComponent {
public:
  RectangleRenderComponent(Point ld, Point ru)
    : RenderComponent(), leftDown(ld), rightUp(ru) {}

  // For now public
  Point leftDown, rightUp;

  void render(SDL_Renderer* renderer, TransformComponent* transform) override;
};

#endif // RECTANGLE_RENDER_COMPONENT_H
