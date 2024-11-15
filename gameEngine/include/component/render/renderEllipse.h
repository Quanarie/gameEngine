#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <SDL.h>
#include <SDL_rect.h>
#include <cmath>
#include <memory>

#include "component/render/render.h"

class EllipseRenderComponent : public RenderComponent {
public:
  EllipseRenderComponent(float width, float height,
                         std::shared_ptr<SDL_Texture> tex = nullptr)
      : RenderComponent(width, height, tex) {}

  void render(SDL_Renderer *renderer, TransformComponent *transform) override {
    float centerX = transform->x;
    float centerY = transform->y;
    float sMajorAxis = width / 2.0f;
    float sMinorAxis = height / 2.0f;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (float angle = 0; angle < 360; angle += 0.1f) {
      float rad = angle * M_PI / 180.0f;
      float x = centerX + sMajorAxis * cos(rad);
      float y = centerY + sMinorAxis * sin(rad);
      SDL_RenderDrawPoint(renderer, static_cast<int>(x), static_cast<int>(y));
    }
  }
};

#endif // ELLIPSE_H
