// #ifndef SPRITE_H
// #define SPRITE_H
//
// #include <SDL_render.h>
// #include <iostream>
//
// #include "component/render/render_component.h"
// #include "component/render/texture_manager.h"
//
// class SpriteRenderComponent : public RenderComponent {
// public:
//   SpriteRenderComponent(float width, float height, std::string pathToSprite,
//                         Point offset = {0, 0})
//       : RenderComponent(width, height, offset) {
//     path = pathToSprite;
//   }
//
//   void initialize(SDL_Renderer *renderer) override {
//     if (!TextureManager::has(path)) {
//       TextureManager::create(path, renderer);
//     }
//   }
//
//   void doRender(SDL_Renderer *renderer,
//                 TransformComponent *transform) override {
//     SDL_Rect dstRect{static_cast<int>(transform->point.x + offset.x),
//                      static_cast<int>(transform->point.y + offset.y),
//                      static_cast<int>(width), static_cast<int>(height)};
//     SDL_RenderCopy(renderer, TextureManager::get(path), nullptr, &dstRect);
//   }
//
// private:
//   std::string path;
// };
//
// #endif // SPRITE_H
