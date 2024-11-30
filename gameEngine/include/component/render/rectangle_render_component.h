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

  void render(SDL_Renderer* renderer,
                TransformComponent* transform) override {
    float transformedLeft = leftDown.x + transform->point.x;
    float transformedTop = leftDown.y + transform->point.y;
    float transformedRight = rightUp.x + transform->point.x;
    float transformedBottom = rightUp.y + transform->point.y;

    SDL_Rect rect;
    rect.x = static_cast<int>(std::round(transformedLeft));
    rect.y = static_cast<int>(std::round(transformedTop));
    rect.w = static_cast<int>(std::round(transformedRight - transformedLeft));
    rect.h = static_cast<int>(std::round(transformedBottom - transformedTop));

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  }
};

#endif // RECTANGLE_RENDER_COMPONENT_H
