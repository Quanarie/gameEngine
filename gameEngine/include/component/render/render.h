#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include <memory>
#include <vector>

#include "component/collider/polygonCollider.h"
#include "component/component.h"
#include "component/transform.h"

class RenderComponent : public Component {
public:
  RenderComponent(float w, float h, std::shared_ptr<SDL_Texture> tex, bool rc)
      : width(w), height(h), texture(tex), renderCollider(rc) {}

  virtual ~RenderComponent() = default;

  virtual void render(SDL_Renderer *renderer, TransformComponent *transform,
                      PolygonColliderComponent *collider = nullptr) {
    doRender(renderer, transform);

    if (renderCollider && collider) {
      renderPolygon(renderer, collider);
    }
  }

protected:
  virtual void doRender(SDL_Renderer *renderer,
                        TransformComponent *transform) = 0;

  void renderPolygon(SDL_Renderer *renderer,
                     PolygonColliderComponent *collider) {
    const std::vector<Point> globalPoints = collider->getGlobalPoints();

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    for (size_t i = 0; i < globalPoints.size(); ++i) {
      const auto &p1 = globalPoints[i];
      const auto &p2 = globalPoints[(i + 1) % globalPoints.size()];
      SDL_RenderDrawLine(renderer, static_cast<int>(p1.x),
                         static_cast<int>(p1.y), static_cast<int>(p2.x),
                         static_cast<int>(p2.y));
    }
  }

  float width, height;
  std::shared_ptr<SDL_Texture> texture;
  bool renderCollider;
};

#endif // RENDER_H
