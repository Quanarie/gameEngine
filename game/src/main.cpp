#include <SDL_render.h>
#include <SDL_scancode.h>

#include "engine.h"
#include "entity.h"
#include "static/inputs.h"
#include "util/vector.h"
#include "static/options.h"
#include "component/transform_component.h"
#include "component/collider/ellipse/ellipse_axes.h"
#include "component/collider/ellipse/ellipse_colider_component.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

class Player : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Vector{10.0f, 0.0f});
    collider = addComponent<RectangleColliderComponent>(
      Vector{5.0f, -5.0f}, Vector{30.0f, 30.0f});
  }

  void update() override {
    if (Inputs::isKeyHeld(SDL_SCANCODE_W)) { transform->position.y += 1; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_S)) { transform->position.y -= 1; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_A)) { transform->position.x -= 1; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_D)) { transform->position.x += 1; }

    Vector toCenter = Vector{0.0f, 0.0f} - transform->position;

    if (Inputs::isMouseButtonHeld(SDL_BUTTON_LEFT)) {
      transform->position = transform->position + Vector{
        (float)(rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1)),
        (float)(rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1))
      } + toCenter / 100;
    }
  }

private:
  TransformComponent* transform = nullptr;
  RenderComponent* render = nullptr;
  ColliderComponent* collider = nullptr;
};

class Enemy : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Vector{100.0f, 0.0f});
    collider = addComponent<EllipseColliderComponent>(
      Vector{0.0f, 0.0f}, EllipseAxes{50.0f, 50.0f});
  }

  void update() override {}

private:
  TransformComponent* transform = nullptr;
  RenderComponent* render = nullptr;
  ColliderComponent* collider = nullptr;
};

class Point : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Vector{0.0f, 0.0f});
    render = addComponent<EllipseRenderComponent>(
      Vector{0.0f, 0.0f}, EllipseAxes{0.5f, 0.5f});
  }

  void update() override {}

private:
  TransformComponent* transform = nullptr;
  RenderComponent* render = nullptr;
};

int main(int argc, char* argv[]) {
  Options::renderColliders = true;

  GameParams params = {(char*const)"game", 800, 600};
  Engine engine(params);

  engine.createEntity<Player>();
  engine.createEntity<Enemy>();

  engine.createEntity<Point>();

  return engine.start();
}
