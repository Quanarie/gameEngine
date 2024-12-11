#include <SDL_render.h>
#include <SDL_scancode.h>

#include "engine.h"
#include "entity.h"
#include "inputs.h"
#include "util/vector.h"
#include "options.h"
#include "component/transform_component.h"
#include "component/collider/rectangle/rectangle_colider_component.h"
#include "component/collider/ellipse/ellipse_axes.h"
#include "component/collider/ellipse/ellipse_colider_component.h"

class Player : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Vector{500.0f, 400.0f});
    // render = addComponent<SpriteRenderComponent>(
    //   50.0f, 50.0f, "../assets/player.bmp", Point{-20.0f, -20.0f});
    collider = addComponent<EllipseColliderComponent>(
      Vector{0.0f, 0.0f}, EllipseAxes{20.0f, 40.0f});
    // collider = addComponent<RectangleColliderComponent>(
    //   Point{0.0f, 0.0f}, Point{30.0f, -30.0f});
  }

  void update() override {
    if (Inputs::isKeyHeld(SDL_SCANCODE_W)) { transform->position.y -= 1; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_S)) { transform->position.y += 1; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_A)) { transform->position.x -= 1; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_D)) { transform->position.x += 1; }

    Vector toCenter = Vector{400.0f, 300.0f} - transform->position;

    if (Inputs::isMouseButtonHeld(SDL_BUTTON_LEFT)) {
      transform->position = transform->position + Vector{
        (float)(rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1)),
        (float)(rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1))
      } + toCenter / 1000;
    }

    if (Inputs::isMouseButtonHeld(SDL_BUTTON_RIGHT)) {
      transform->position = transform->position + Vector{
        // (float)(rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1)),
        0.0f,
        (float)(rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1))
      };
    };
  }

private:
  TransformComponent* transform = nullptr;
  RenderComponent* render = nullptr;
  ColliderComponent* collider = nullptr;
};

class Enemy : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Vector{400.0f, 300.0f});
    // render = addComponent<SpriteRenderComponent>(
    //   50.0f, 50.0f, "../assets/enemy.bmp", Point{-25.0f, -25.0f});
    collider = addComponent<RectangleColliderComponent>(
      Vector{0.0f, 0.0f}, Vector{30.0f, -30.0f});
    // collider = addComponent<EllipseColliderComponent>(
    //    Point{0.0f, 0.0f}, EllipseAxes{20.0f, 40.0f});
  }

  void update() override {
    // transform->point.y += 0.1;
  }

private:
  TransformComponent* transform = nullptr;
  RenderComponent* render = nullptr;
  ColliderComponent* collider = nullptr;
};

int main(int argc, char* argv[]) {
  Options::renderColliders = true;

  GameParams params = {(char*const)"game", 800, 600};
  Engine engine(params);

  engine.createEntity<Player>();
  engine.createEntity<Enemy>();
  // for (int i = 0; i < 100; i++) {
  // }

  return engine.start();
}
