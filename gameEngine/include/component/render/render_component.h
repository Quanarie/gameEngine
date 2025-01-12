#ifndef RENDER_H
#define RENDER_H

#include <SDL_render.h>

#include "component/component.h"

class TransformComponent;

class RenderComponent : public Component {
public:
  void initialize() override;
  virtual void render(SDL_Renderer* renderer) {}
protected:
  TransformComponent* transform;
};

#endif // RENDER_H
