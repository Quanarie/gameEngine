#ifndef RECTANGLE_RENDER_COMPONENT_H
#define RECTANGLE_RENDER_COMPONENT_H

#include "render_component.h"

class RectangleRenderComponent : public RenderComponent {
public:
  RectangleRenderComponent(Vector ld, Vector ru)
    : RenderComponent(), leftDown(ld), rightUp(ru) {}

  // For now public
  Vector leftDown, rightUp;

  void render(SDL_Renderer* renderer) override;
};

#endif // RECTANGLE_RENDER_COMPONENT_H
