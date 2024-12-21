#include <list>
#include <chrono>
#include <SDL_scancode.h>

#include "engine.h"
#include "entity.h"
#include "util/vector.h"
#include "static/inputs.h"
#include "static/options.h"
#include "component/transform_component.h"
#include "component/collider/ellipse/ellipse_axes.h"
#include "component/collider/ellipse/ellipse_colider_component.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

class Platform : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Vector{
        static_cast<float>(rand() % 800 - 400),
        static_cast<float>(rand() % 600 - 300),
      }
    );
    render = addComponent<EllipseRenderComponent>(
      Vector{0.0f, 0.0f}, EllipseAxes{20.0f, 20.0f});
  }

  void update() override {}

  TransformComponent* transform = nullptr;
  RenderComponent* render = nullptr;
  ColliderComponent* collider = nullptr;
};

class Player : public Entity {
public:
  Player(std::vector<Platform*> platforms) {
    this->platforms = platforms;
  }

  void initialize() override {
    transform = addComponent<TransformComponent>(Vector{0.0f, 0.0f}, 0.0f, Vector{1.0f, 2.0f});
    collider = addComponent<RectangleColliderComponent>(
      Vector{-15.0f, -15.0f}, Vector{15.0f, 15.0f});
  }

  void update() override {
    if (Inputs::isKeyHeld(SDL_SCANCODE_W)) { transform->pos.y += 3; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_S)) { transform->pos.y -= 3; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_A)) { transform->pos.x -= 3; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_D)) { transform->pos.x += 3; }

    if (prevJumpTime + jumpReloadDuration > now())
      return;

    TransformComponent* myTr = this->transform;
    int wM = Inputs::isKeyHeld(SDL_SCANCODE_UP),
        sM = Inputs::isKeyHeld(SDL_SCANCODE_DOWN),
        aM = Inputs::isKeyHeld(SDL_SCANCODE_LEFT),
        dM = Inputs::isKeyHeld(SDL_SCANCODE_RIGHT);

    if (!wM && !sM && !aM && !dM)
      return;

    prevJumpTime = now();

    Platform* platformToMoveTo = getClosestPlatformToPoint(Vector{
      myTr->pos.x + 100.0f * dM - 100.0f * aM,
      myTr->pos.y + 100.0f * wM - 100.0f * sM, // for now
    });

    if (!platformToMoveTo)
      return;

    myTr->pos = platformToMoveTo->transform->pos;
    this->currentPlatform = platformToMoveTo;
  }

private:
  Platform* getClosestPlatformToPoint(Vector p) {
    Platform* closest = nullptr;
    float closestDist = std::numeric_limits<float>::max();
    for (int i = 0; i < this->platforms.size(); i++) {
      if (this->currentPlatform == this->platforms[i])
        continue;
      float distToPlt = (p - this->platforms[i]->transform->pos).length();
      if (distToPlt < closestDist) {
        closest = this->platforms[i];
        closestDist = distToPlt;
      }
    }
    return closest;
  }

  long long now() {
    return std::chrono::system_clock::now().time_since_epoch().count();
  }

  TransformComponent* transform = nullptr;
  RenderComponent* render = nullptr;
  ColliderComponent* collider = nullptr;
  std::vector<Platform*> platforms;
  Platform* currentPlatform = nullptr;

  const long long jumpReloadDuration = 0.2 * 1000000;
  long long prevJumpTime = now();
};

class Enemy : public Entity {
public:
  void initialize() override {
    transform = addComponent<TransformComponent>(Vector{100.0f, 0.0f}, 0.0f, Vector{0.5f, 1.0f});
    collider = addComponent<EllipseColliderComponent>(
      Vector{0.0f, 0.0f}, EllipseAxes{30.0f, 30.0f});
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

  std::vector<Platform*> platforms;
  platforms.reserve(10);
  for (int i = 0; i < 10; i++) {
    // platforms.push_back(engine.createEntity<Platform>());
  }
  engine.createEntity<Player>(platforms);
  engine.createEntity<Enemy>();

  engine.createEntity<Point>();

  return engine.start();
}
