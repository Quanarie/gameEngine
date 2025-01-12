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
  void initialize() override;
  virtual ~ColliderComponent() = default;

  bool isStatic = false;
  Vector prevPos{};
  RenderComponent* colliderBoundsRenderComponent = nullptr;
  TransformComponent* transform = nullptr;

  // Double dispatch. Nice !!
  virtual bool resolve(const ColliderComponent& other) const = 0;
  virtual bool resolveWith(const RectangleColliderComponent& rect) const = 0;
  virtual bool resolveWith(const EllipseColliderComponent& ellipse) const = 0;

  void render(SDL_Renderer* renderer) const;
};


#endif // COLLIDER_COMPONENT_H
