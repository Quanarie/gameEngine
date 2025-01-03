#ifndef SPRITE_H
#define SPRITE_H

#include <SDL_render.h>
#include <iostream>

#include "component/transform_component.h"
#include "component/render/render_component.h"
#include "component/render/texture_manager.h"

class SpriteRenderComponent : public RenderComponent {
public:
  Uint8 r = 255, g = 255, b = 255;

  SpriteRenderComponent(float w, float h, std::string p, Vector os = {0, 0})
    : width(w), height(h), path(std::move(p)), offset(os) {}

  void initializeWithSdlRenderer(SDL_Renderer* renderer) override;
  void render(SDL_Renderer* renderer) override;

private:
  std::string path;
  float width, height;
  Vector offset;
};

#endif // SPRITE_H
