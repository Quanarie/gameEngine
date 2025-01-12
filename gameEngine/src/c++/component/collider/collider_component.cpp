#include "entity.h"
#include "component/transform_component.h"
#include "component/collider/collider_component.h"

#include <__format/format_functions.h>

void ColliderComponent::render(SDL_Renderer* renderer) const { colliderBoundsRenderComponent->render(renderer); }

void ColliderComponent::initialize()
{
  transform = entity->getComponent<TransformComponent>();
  if (!transform)
    throw std::runtime_error(std::format("Not found transformComponent on collider of entity: {}",
                                         typeid(entity).name()));
}
