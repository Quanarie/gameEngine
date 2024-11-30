#include <SDL_render.h>

#include "component/transform_component.h"
#include "component/render/rectangle_render_component.h"

void RectangleRenderComponent::render(SDL_Renderer* renderer,
                                      TransformComponent* transform) {
  float transformedLeft = leftDown.x + transform->point.x;
  float transformedTop = leftDown.y + transform->point.y;
  float transformedRight = rightUp.x + transform->point.x;
  float transformedBottom = rightUp.y + transform->point.y;

  int left = static_cast<int>(transformedLeft);
  int top = static_cast<int>(transformedTop);
  int right = static_cast<int>(transformedRight);
  int bottom = static_cast<int>(transformedBottom);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(renderer, left, top, right, top);
  SDL_RenderDrawLine(renderer, right, top, right, bottom);
  SDL_RenderDrawLine(renderer, right, bottom, left, bottom);
  SDL_RenderDrawLine(renderer, left, bottom, left, top);
}
