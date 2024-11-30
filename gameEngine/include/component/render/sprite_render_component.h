#ifndef SPRITE_H
#define SPRITE_H

#include <SDL_render.h>
#include <iostream>

#include "component/transform_component.h"
#include "component/render/render_component.h"
#include "component/render/texture_manager.h"

class SpriteRenderComponent : public RenderComponent {
public:
  SpriteRenderComponent(float w, float h, std::string p,
                        Point os = {0, 0})
    : width(w), height(h), path(std::move(p)), offset(os) {}

  void initialize(SDL_Renderer* renderer) override {
    if (!TextureManager::has(path)) {
      TextureManager::create(path, renderer);
    }
  }

  void render(SDL_Renderer* renderer,
                TransformComponent* transform) override {
    SDL_Rect dstRect{
      static_cast<int>(transform->point.x + offset.x),
      static_cast<int>(transform->point.y + offset.y),
      static_cast<int>(width), static_cast<int>(height)
    };
    SDL_RenderCopy(renderer, TextureManager::get(path), nullptr, &dstRect);
  }

private:
  std::string path;
  float width, height;
  Point offset;
};

#endif // SPRITE_H
