#include "entity.h"
#include "static/coordinates_converter.h"
#include "component/render/sprite_render_component.h"

void SpriteRenderComponent::initialize(SDL_Renderer* renderer) {
  RenderComponent::initialize(renderer);
  if (!TextureManager::has(path)) {
    TextureManager::create(path, renderer);
  }
}

void SpriteRenderComponent::render(SDL_Renderer* renderer) {
  Vector positionInSdlCoords = CoordinatesConverter::toSdlCoordinates(transform->position);

  SDL_Rect dstRect{
    static_cast<int>(positionInSdlCoords.x + offset.x),
    static_cast<int>(positionInSdlCoords.y + offset.y),
    static_cast<int>(width), static_cast<int>(height)
  };
  SDL_RenderCopy(renderer, TextureManager::get(path), nullptr, &dstRect);
}
