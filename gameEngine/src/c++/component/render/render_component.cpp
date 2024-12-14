#include "entity.h"
#include "component/transform_component.h"
#include "component/render/render_component.h"

void RenderComponent::initialize(SDL_Renderer* renderer) {
  this->transform = this->entity->getComponent<TransformComponent>();
}
