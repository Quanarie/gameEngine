#include <SDL_render.h>

#include "static/coordinates_converter.h"
#include "component/transform_component.h"
#include "component/render/rectangle_render_component.h"

void RectangleRenderComponent::render(SDL_Renderer* renderer,
                                      TransformComponent* transform) {
  // TODO: make a way to get components in other components without user or engine.cpp
  // having to pass as arguments. If enough take out similar logic from renderers and colliders:
  // transformed position ...
  Vector transLD = leftDown * Vector{1.0f, -1.0f} + CoordinatesConverter::toSdlCoordinates(transform->position);
  Vector transRU = rightUp * Vector{1.0f, -1.0f} + CoordinatesConverter::toSdlCoordinates(transform->position);

  int left = static_cast<int>(transLD.x);
  int top = static_cast<int>(transLD.y);
  int right = static_cast<int>(transRU.x);
  int bottom = static_cast<int>(transRU.y);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(renderer, left, top, right, top);
  SDL_RenderDrawLine(renderer, right, top, right, bottom);
  SDL_RenderDrawLine(renderer, right, bottom, left, bottom);
  SDL_RenderDrawLine(renderer, left, bottom, left, top);
}
