#include "static/coordinates_converter.h"
#include "component/render/sprite_render_component.h"

void SpriteRenderComponent::changeImage(std::string newPath)
{
  path = newPath;
  if (!TextureManager::has(path)) { TextureManager::create(path); }
}

void SpriteRenderComponent::initialize()
{
  RenderComponent::initialize();
  if (path.empty()) { return; }
  if (!TextureManager::has(path)) { TextureManager::create(path); }
}

void SpriteRenderComponent::render(SDL_Renderer* renderer)
{
  Vector positionInSdlCoords = CoordinatesConverter::toSdlCoordinates(transform->pos);

  SDL_Rect dstRect{
    // TODO: Offset is only scaled here. I think i dont need to scale center in ellipse?
    static_cast<int>(positionInSdlCoords.x + offset.x * transform->scale.x),
    static_cast<int>(positionInSdlCoords.y + offset.y * transform->scale.y),
    static_cast<int>(width * transform->scale.x),
    static_cast<int>(height * transform->scale.y)
  };

  if (path.empty())
    return;

  SDL_Texture* texture = TextureManager::get(path);
  SDL_SetTextureColorMod(texture, r, g, b);
  SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
  SDL_SetTextureColorMod(texture, 255, 255, 255);
}
