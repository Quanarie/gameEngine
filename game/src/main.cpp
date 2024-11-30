#include <SDL_render.h>
#include <SDL_scancode.h>

#include "component/collider/collider_component.h"
#include "component/render/sprite_render_component.h"
#include "component/transform_component.h"
#include "engine.h"
#include "entity.h"
#include "inputs.h"
#include "math/point.h"
#include "options.h"
#include "component/collider/rectangle_colider_component.h"
#include "component/render/rectangle_render_component.h"

class Player : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Point{400.0f, 300.0f}, 0.0f,
                                                 1.0f, 1.0f);
    // render = addComponent<SpriteRenderComponent>(
    //   50.0f, 50.0f, "../assets/player.bmp", Point{-20.0f, -20.0f});
    render = addComponent<RectangleRenderComponent>(
      Point{-25.0f, -25.0f}, Point{25.0f, 25.0f});
    collider = addComponent<RectangleColliderComponent>(
      Point{-25.0f, -25.0f}, Point{25.0f, 25.0f});
  }

  void update() override {
    if (Inputs::isKeyHeld(SDL_SCANCODE_W)) { transform->point.y -= 1; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_S)) { transform->point.y += 1; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_A)) { transform->point.x -= 1; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_D)) { transform->point.x += 1; }

    if (Inputs::isMouseButtonHeld(SDL_BUTTON_LEFT)) {
      transform->point.x += rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1);
      transform->point.y += rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1);
    }
  }

private:
  TransformComponent* transform;
  RectangleRenderComponent* render;
  ColliderComponent* collider;
};

class Enemy : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Point{400.0f, 300.0f}, 0.0f,
                                                 1.0f, 1.0f);
    // render = addComponent<SpriteRenderComponent>(
    //   50.0f, 50.0f, "../assets/enemy.bmp", Point{-20.0f, -20.0f});
    render = addComponent<RectangleRenderComponent>(
      Point{-25.0f, -25.0f}, Point{25.0f, 25.0f});
    collider = addComponent<RectangleColliderComponent>(
      Point{-25.0f, -25.0f}, Point{25.0f, 25.0f});
  }

  void update() override {}

private:
  TransformComponent* transform = nullptr;
  RectangleRenderComponent* render = nullptr;
  ColliderComponent* collider = nullptr;
};

int main(int argc, char* argv[]) {
  Options::renderColliders = true;

  GameParams params = {(char*const)"game", 800, 600};
  Engine engine(params);

  engine.createEntity<Player>();
  engine.createEntity<Enemy>();

  return engine.start();
}
