#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H
#include "component/component.h"

class RectangleColliderComponent;
class TransformComponent;

class ColliderComponent : public Component {
public:
  virtual ~ColliderComponent() = default;

  virtual bool detect(const ColliderComponent& other,
                      const TransformComponent& transformThis,
                      const TransformComponent& transformOther) const = 0;

  virtual bool detectWith(const RectangleColliderComponent& rect,
                          const TransformComponent& transformThis,
                          const TransformComponent& transformOther) const = 0;

  // virtual bool detectWith(const EllipseColliderComponent& ellipse,
  //                         const TransformComponent& transformThis,
  //                         const TransformComponent& transformOther) const = 0;
};


#endif // COLLIDER_COMPONENT_H
