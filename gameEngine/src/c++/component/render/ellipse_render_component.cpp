#include "static/coordinates_converter.h"
#include "component/transform_component.h"
#include "component/render/ellipse_render_component.h"

void EllipseRenderComponent::render(SDL_Renderer* renderer) {
  Vector center = CoordinatesConverter::toSdlCoordinates(transform->pos);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  for (float angle = 0; angle < 360; angle += 1) {
    float rad = angle * M_PI / 180.0f;
    Vector c = center;
    float x = c.x + axes.sMajor*transform->scale.x * cos(rad);
    float y = c.y + axes.sMinor*transform->scale.y * sin(rad);

    float rot = this->transform->getRotationRad();
    float xRotated = c.x + (x - c.x) * cos(rot) - (y - c.y) * sin(rot);
    float yRotated = c.y + (x - c.x) * sin(rot) + (y - c.y) * cos(rot);
    SDL_RenderDrawPoint(renderer, static_cast<int>(xRotated), static_cast<int>(yRotated));
  }
}
