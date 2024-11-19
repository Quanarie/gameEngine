#include <SDL_render.h>
#include <SDL_scancode.h>
#include <initializer_list>

#include "component/collider/polygonCollider.h"
#include "component/render/spriteRender.h"
#include "component/transform.h"
#include "engine.h"
#include "entity.h"
#include "inputs.h"
#include "math/point.h"
#include "options.h"

class Player : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Point{400.0f, 300.0f}, 0.0f,
                                                 1.0f, 1.0f);
    render = addComponent<SpriteRenderComponent>(
        50.0f, 50.0f, "../assets/player.bmp", Point{-20.0f, -20.0f});
    collider = addComponent<PolygonColliderComponent>(
        std::initializer_list<Point>{
            {25.0f, 25.0f}, {-25.0f, 25.0f}, {-25.0f, -25.0f}, {25.0f, -25.0f}},
        transform);
  }
  void update() override {
    if (Inputs::isKeyHeld(SDL_SCANCODE_W)) {
      transform->point.y -= 1;
    }
    if (Inputs::isKeyHeld(SDL_SCANCODE_S)) {
      transform->point.y += 1;
    }
    if (Inputs::isKeyHeld(SDL_SCANCODE_A)) {
      transform->point.x -= 1;
    }
    if (Inputs::isKeyHeld(SDL_SCANCODE_D)) {
      transform->point.x += 1;
    }

    if (Inputs::isMouseButtonHeld(SDL_BUTTON_LEFT)) {
      transform->point.x += rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1);
      transform->point.y += rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1);
    }
  }

private:
  TransformComponent *transform;
  SpriteRenderComponent *render;
  PolygonColliderComponent *collider;
};

class Enemy : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Point{400.0f, 300.0f}, 0.0f,
                                                 1.0f, 1.0f);
    render = addComponent<SpriteRenderComponent>(
        50.0f, 50.0f, "../assets/enemy.bmp", Point{-20.0f, -20.0f});
    collider = addComponent<PolygonColliderComponent>(
        std::initializer_list<Point>{
            {25.0f, 25.0f}, {-25.0f, 25.0f}, {-25.0f, -25.0f}, {25.0f, -25.0f}},
        transform);
  }
  void update() override {}

private:
  TransformComponent *transform;
  SpriteRenderComponent *render;
  PolygonColliderComponent *collider;
};

int main(int argc, char *argv[]) {
  Options::renderColliders = true;

  GameParams params = {(char *const)"game", 800, 600};
  Engine engine(params);

  for (int i = 0; i < 1; i++) {
    engine.createEntity<Player>();
  }

  engine.createEntity<Enemy>();

  return engine.start();
}
