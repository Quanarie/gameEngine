#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "component/transform_component.h"
#include "component/render/render_component.h"

class EllipseRenderComponent : public RenderComponent {
public:
  Point center;
  Point radiuses;

  EllipseRenderComponent(Point c, Point r)
    : center(c), radiuses(r) {}

  void render(SDL_Renderer *renderer,
                TransformComponent *transform) override {
    float centerX = transform->point.x;
    float centerY = transform->point.y;
    float sMajorAxis = radiuses.x;
    float sMinorAxis = radiuses.y;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (float angle = 0; angle < 360; angle += 1) {
      float rad = angle * M_PI / 180.0f;
      float x = centerX + sMajorAxis * cos(rad);
      float y = centerY + sMinorAxis * sin(rad);
      SDL_RenderDrawPoint(renderer, static_cast<int>(x), static_cast<int>(y));
    }
  }
};

#endif // ELLIPSE_H
