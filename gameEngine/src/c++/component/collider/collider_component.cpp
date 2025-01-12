#include "entity.h"
#include "component/transform_component.h"
#include "component/collider/collider_component.h"

void ColliderComponent::render(SDL_Renderer* renderer) const { colliderBoundsRenderComponent->render(renderer); }

void ColliderComponent::initialize() { this->transform = this->entity->getComponent<TransformComponent>(); }
