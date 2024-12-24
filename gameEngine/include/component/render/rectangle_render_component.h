#ifndef RECTANGLE_RENDER_COMPONENT_H
#define RECTANGLE_RENDER_COMPONENT_H

#include <optional>
#include <static/geometry.h>

#include "render_component.h"
#include "component/collider/rectangle/rectangle_corners.h"

class RectangleRenderComponent : public RenderComponent {
public:
  RectangleRenderComponent(Vector ld, Vector ru)
    : RenderComponent(), leftDown(ld), rightUp(ru) {}

  // For now public
  Vector leftDown, rightUp;

  void render(SDL_Renderer* renderer) override;
};

#endif // RECTANGLE_RENDER_COMPONENT_H
