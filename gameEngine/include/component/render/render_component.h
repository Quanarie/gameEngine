#ifndef RENDER_H
#define RENDER_H

#include <SDL_render.h>

#include "component/component.h"

class TransformComponent;

class RenderComponent : public Component {
public:
  virtual void initialize(SDL_Renderer* renderer);
  virtual void render(SDL_Renderer* renderer) {}
protected:
  TransformComponent* transform;
};

#endif // RENDER_H
