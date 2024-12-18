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

  bool isStatic = false;
  RenderComponent* colliderBoundsRenderComponent = nullptr;

  // Double dispatch. Nice !!
  virtual bool detect(const ColliderComponent& other,
                       TransformComponent& transformThis,
                       TransformComponent& transformOther) const = 0;

  virtual bool detectWith(const RectangleColliderComponent& rect,
                           TransformComponent& transformThis,
                           TransformComponent& transformOther) const = 0;

  virtual bool detectWith(const EllipseColliderComponent& ellipse,
                           TransformComponent& transformThis,
                           TransformComponent& transformOther) const = 0;

  void render(SDL_Renderer* renderer) const;
};


#endif // COLLIDER_COMPONENT_H
