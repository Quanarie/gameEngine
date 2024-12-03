#include "component/collider/collider_component.h"

void ColliderComponent::render(SDL_Renderer* renderer, TransformComponent* transform) const {
  if (colliderBoundsRenderComponent != nullptr) {
    colliderBoundsRenderComponent->render(renderer, transform);
  }
}
