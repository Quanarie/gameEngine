#include "component/render/sprite_render_component.h"

void SpriteRenderComponent::initialize(SDL_Renderer* renderer) {
  if (!TextureManager::has(path)) {
    TextureManager::create(path, renderer);
  }
}

void SpriteRenderComponent::render(SDL_Renderer* renderer,
                                   TransformComponent* transform) {
  SDL_Rect dstRect{
    static_cast<int>(transform->point.x + offset.x),
    static_cast<int>(transform->point.y + offset.y),
    static_cast<int>(width), static_cast<int>(height)
  };
  SDL_RenderCopy(renderer, TextureManager::get(path), nullptr, &dstRect);
}
