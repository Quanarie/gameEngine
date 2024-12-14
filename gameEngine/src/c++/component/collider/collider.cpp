#include "component/collider/collider_component.h"

void ColliderComponent::render(SDL_Renderer* renderer) const {
  if (colliderBoundsRenderComponent != nullptr) {
    colliderBoundsRenderComponent->render(renderer);
  }
}
