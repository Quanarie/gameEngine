#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include <memory>

#include "component/component.h"
#include "component/transform.h"

class RenderComponent : public Component {
public:
  RenderComponent(float w, float h, std::shared_ptr<SDL_Texture> tex)
      : width(w), height(h), texture(tex) {}

  virtual ~RenderComponent() = default;

  virtual void render(SDL_Renderer *renderer,
                      TransformComponent *transform) = 0;

protected:
  float width, height;
  std::shared_ptr<SDL_Texture> texture;
};

#endif // RENDER_H
