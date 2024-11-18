#include <SDL_scancode.h>
#include <initializer_list>

#include "component/collider/polygonCollider.h"
#include "component/render/ellipseRender.h"
#include "component/transform.h"
#include "engine.h"
#include "entity.h"
#include "inputs.h"

class Player : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Point{400.0f, 300.0f}, 0.0f,
                                                 1.0f, 1.0f);
    render = addComponent<EllipseRenderComponent>(50.0f, 50.0f, nullptr, true);
    collider = addComponent<PolygonColliderComponent>(
        std::initializer_list<Point>{
            {25.0f, 25.0f}, {-25.0f, 25.0f}, {-25.0f, -25.0f}, {25.0f, -25.0f}},
        transform);
  }
  void update() override {
    if (Inputs::IsKeyHeld(SDL_SCANCODE_W)) {
      transform->point.y -= 1;
    }
    if (Inputs::IsKeyHeld(SDL_SCANCODE_S)) {
      transform->point.y += 1;
    }
    if (Inputs::IsKeyHeld(SDL_SCANCODE_A)) {
      transform->point.x -= 1;
    }
    if (Inputs::IsKeyHeld(SDL_SCANCODE_D)) {
      transform->point.x += 1;
    }

    if (Inputs::IsMouseButtonHeld(SDL_BUTTON_LEFT)) {
      transform->point.x += rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1);
      transform->point.y += rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1);
    }
  }

private:
  TransformComponent *transform;
  EllipseRenderComponent *render;
  PolygonColliderComponent *collider;
};

int main(int argc, char *argv[]) {
  GameParams params = {(char *const)"game", 800, 600};
  Engine engine(params);

  for (int i = 0; i < 1; i++) {
    engine.createEntity<Player>();
  }

  return engine.start();
}
