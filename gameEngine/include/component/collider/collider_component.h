#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include <SDL_render.h>

#include "component/component.h"
#include "component/render/render_component.h"

class TransformComponent;
class RectangleColliderComponent;
class EllipseColliderComponent;

class ColliderComponent : public Component {
public:
  virtual ~ColliderComponent() = default;

  // Double dispatch. Nice !!
  virtual bool detect(const ColliderComponent& other,
                      const TransformComponent& transformThis,
                      const TransformComponent& transformOther) const = 0;

  virtual bool detectWith(const RectangleColliderComponent& rect,
                          const TransformComponent& transformThis,
                          const TransformComponent& transformOther) const = 0;

  virtual bool detectWith(const EllipseColliderComponent& ellipse,
                          const TransformComponent& transformThis,
                          const TransformComponent& transformOther) const = 0;

  void render(SDL_Renderer* renderer, TransformComponent* transform) const;

protected:
  RenderComponent* colliderBoundsRenderComponent = nullptr;
};


#endif // COLLIDER_COMPONENT_H
