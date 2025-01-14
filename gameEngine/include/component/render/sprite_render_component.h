#ifndef SPRITE_RENDER_COMPONENT_H
#define SPRITE_RENDER_COMPONENT_H

#include <iostream>
#include <SDL_render.h>

#include "component/transform_component.h"
#include "component/render/render_component.h"
#include "component/render/texture_manager.h"

class SpriteRenderComponent : public RenderComponent
{
public:
  Uint8 r = 255, g = 255, b = 255;

  SpriteRenderComponent(float w, float h, std::string p = "", Vector os = {0, 0})
    : width(w), height(h), currentlyPlayedFromPath(p), offset(os), initialPath(p) {}

  void initialize() override;
  void render(SDL_Renderer* renderer) override;

  void changeImage(std::string newPath);
  void setInitialImage() { currentlyPlayedFromPath = initialPath; }

private:
  std::string initialPath;
  std::string currentlyPlayedFromPath;
  float width, height;
  Vector offset;
};

#endif // SPRITE_RENDER_COMPONENT_H
