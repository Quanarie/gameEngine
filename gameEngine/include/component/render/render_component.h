#ifndef RENDER_H
#define RENDER_H

#include <SDL_render.h>

#include "component/collider/collider_component.h"
#include "component/component.h"
#include "component/transform_component.h"

class RenderComponent : public Component {
public:
  virtual void render(SDL_Renderer* renderer, TransformComponent* transform) {}
};

#endif // RENDER_H
