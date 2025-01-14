#include "static/coordinates_converter.h"
#include "component/render/sprite_render_component.h"

void SpriteRenderComponent::changeImage(std::string newPath)
{
  // The order of these calls is very important, this function is called by worker thread
  if (!TextureManager::has(newPath)) { TextureManager::create(newPath); }
  currentlyPlayedFromPath = newPath;
}

void SpriteRenderComponent::initialize()
{
  RenderComponent::initialize();
  if (currentlyPlayedFromPath.empty()) { return; }
  if (!TextureManager::has(currentlyPlayedFromPath)) { TextureManager::create(currentlyPlayedFromPath); }
}

void SpriteRenderComponent::render(SDL_Renderer* renderer)
{
  Vector positionInSdlCoords = CoordinatesConverter::toSdlCoordinates(transform->pos);

  SDL_Rect dstRect{
    static_cast<int>(positionInSdlCoords.x + offset.x * transform->scale.x),
    static_cast<int>(positionInSdlCoords.y + offset.y * transform->scale.y),
    static_cast<int>(width * transform->scale.x),
    static_cast<int>(height * transform->scale.y)
  };

  if (currentlyPlayedFromPath.empty())
    return;

  SDL_Texture* texture = TextureManager::get(currentlyPlayedFromPath);
  SDL_SetTextureColorMod(texture, r, g, b);
  SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
  SDL_SetTextureColorMod(texture, 255, 255, 255);
}
