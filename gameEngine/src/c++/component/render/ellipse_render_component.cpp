#include "component/render/ellipse_render_component.h"
#include "component/transform_component.h"

void EllipseRenderComponent::render(SDL_Renderer* renderer,
                                    TransformComponent* transform) {
  float centerX = transform->position.x;
  float centerY = transform->position.y;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  for (float angle = 0; angle < 360; angle += 1) {
    float rad = angle * M_PI / 180.0f;
    float x = centerX + axes.sMajor * cos(rad);
    float y = centerY + axes.sMinor * sin(rad);
    SDL_RenderDrawPoint(renderer, static_cast<int>(x), static_cast<int>(y));
  }
}
