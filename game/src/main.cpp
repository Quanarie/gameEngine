#include <list>
#include <chrono>
#include <SDL_scancode.h>
#include <component/render/sprite_render_component.h>

#include "engine.h"
#include "entity.h"
#include "util/vector.h"
#include "static/inputs.h"
#include "static/options.h"
#include "component/transform_component.h"
#include "component/collider/ellipse/ellipse_axes.h"
#include "component/collider/ellipse/ellipse_colider_component.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

#define WAIT(prev, reload) if ((prev) + (reload) > now()) return; prev = now();
#define PLATFORM_TOO_CLOSE_DISTANCE 25.0f

long long now() { return std::chrono::system_clock::now().time_since_epoch().count(); }

class Platform : public Entity
{
public:
  void initialize() override
  {
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

bool positiveXContraint(const Vector& myPos, const Vector& constrainedPos)
{
  return constrainedPos.x > myPos.x + PLATFORM_TOO_CLOSE_DISTANCE;
}

bool negativeXContraint(const Vector& myPos, const Vector& constrainedPos)
{
  return constrainedPos.x < myPos.x - PLATFORM_TOO_CLOSE_DISTANCE;
}

bool positiveYContraint(const Vector& myPos, const Vector& constrainedPos)
{
  return constrainedPos.y > myPos.y + PLATFORM_TOO_CLOSE_DISTANCE;
}

bool negativeYContraint(const Vector& myPos, const Vector& constrainedPos)
{
  return constrainedPos.y < myPos.y - PLATFORM_TOO_CLOSE_DISTANCE;
}

class Player : public Entity
{
public:
  Player(std::vector<Platform*> platforms) { this->platforms = platforms; }

  void initialize() override
  {
    transform = addComponent<TransformComponent>(Vector{0.0f, 0.0f}, 30.0f, Vector{1.25f, 1.25f});
    collider = addComponent<RectangleColliderComponent>(
      Vector{-30.0f, -30.0f}, Vector{30.0f, 30.0f});
    render = addComponent<SpriteRenderComponent>(
      35.0f, 40.0f, "../assets/player.bmp", Vector{-16.0f, -18.0f});
  }

  void update() override
  {
    tiltToNormal();

    if (Inputs::isKeyHeld(SDL_SCANCODE_W)) { transform->pos.y += 3; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_S)) { transform->pos.y -= 3; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_A)) { transform->pos.x -= 3; }
    if (Inputs::isKeyHeld(SDL_SCANCODE_D)) { transform->pos.x += 3; }

    int wM = Inputs::isKeyPressed(SDL_SCANCODE_UP),
        sM = Inputs::isKeyPressed(SDL_SCANCODE_DOWN),
        aM = Inputs::isKeyPressed(SDL_SCANCODE_LEFT),
        dM = Inputs::isKeyPressed(SDL_SCANCODE_RIGHT);

    if (!wM && !sM && !aM && !dM)
      return;

    std::vector<std::function<bool(const Vector&, const Vector&)>> constraints;
    if (wM) constraints.push_back(positiveYContraint);
    if (sM) constraints.push_back(negativeYContraint);
    if (aM) constraints.push_back(negativeXContraint);
    if (dM) constraints.push_back(positiveXContraint);

    Platform* platformToMoveTo = getClosestPlatformWithDisjunctiveContraints(constraints);

    if (!platformToMoveTo)
      return;

    this->transform->pos = platformToMoveTo->transform->pos;
  }

  void decreaseHp(int amount)
  {
    tiltToRed();
    this->hp -= amount;
    if (this->hp <= 0)
      respawn();
  }

  TransformComponent* getTransform() { return transform; }

private:
  void tiltToNormal()
  {
    this->render->g = std::min(255, this->render->g + 5);
    this->render->b = std::min(255, this->render->b + 5);
  }

  void tiltToRed()
  {
    this->render->g = std::max(0, this->render->g - 100);
    this->render->b = std::max(0, this->render->b - 100);
  }

  void respawn()
  {
    this->transform->pos = Vector{0.0f, 0.0f};
    this->hp = 10;
  }

  Platform* getClosestPlatformWithDisjunctiveContraints(
    const std::vector<std::function<bool(const Vector&, const Vector&)>>& constraints)
  {
    Platform* closest = nullptr;
    float closestDist = std::numeric_limits<float>::max();
    for (int i = 0; i < this->platforms.size(); i++)
    {
      bool passesAtLeastOneConstraint = false;
      for (const auto& constraint : constraints)
      {
        if (constraint(this->transform->pos, this->platforms[i]->transform->pos))
        {
          passesAtLeastOneConstraint = true;
          break;
        }
      }

      if (!passesAtLeastOneConstraint)
        continue;

      float distToPlt = (this->transform->pos - this->platforms[i]->transform->pos).length();
      if (distToPlt < closestDist)
      {
        closest = this->platforms[i];
        closestDist = distToPlt;
      }
    }
    return closest;
  }

  TransformComponent* transform = nullptr;
  SpriteRenderComponent* render = nullptr;
  ColliderComponent* collider = nullptr;
  std::vector<Platform*> platforms;

  int hp = 100000000;
};

class Enemy : public Entity
{
public:
  Enemy(Player* player) { this->player = player; }

  void initialize() override
  {
    transform = addComponent<TransformComponent>(Vector{100.0f, 0.0f}, 0.0f, Vector{1.25f, 1.25f});
    collider = addComponent<EllipseColliderComponent>(
      Vector{0.0f, 0.0f}, EllipseAxes{15.0f, 25.0f});
    // render = addComponent<SpriteRenderComponent>(
    //   40.0f, 40.0f, "../assets/enemy.bmp", Vector{-19.0f, -19.0f});
  }

  void update() override
  {
    // transform->pos = transform->pos + (player->getTransform()->pos - transform->pos).normalized() / 2;
    // transform->pos.x -= 0.25f;
    // transform->pos.y -= 0.25f;
  }

  void onCollision(ColliderComponent* col) override
  {
    WAIT(prevHitTime, hitReload);
    auto player = dynamic_cast<Player*>(col->entity);
    if (!player)
      return;
    player->decreaseHp(1);
  }

private:
  TransformComponent* transform = nullptr;
  RenderComponent* render = nullptr;
  ColliderComponent* collider = nullptr;
  Player* player = nullptr;

  long long hitReload = 0.5 * 1000000;
  long long prevHitTime = now();
};

class Point : public Entity
{
public:
  Point(Vector p) { this->pos = p; }

  void initialize() override
  {
    transform = addComponent<TransformComponent>(this->pos, 45.0f);
    render = addComponent<EllipseRenderComponent>(
      Vector{0.0f, 0.0f}, EllipseAxes{0.5f, 0.5f});
  }

  void update() override {}

private:
  Vector pos;
  TransformComponent* transform = nullptr;
  RenderComponent* render = nullptr;
};

int main(int argc, char* argv[])
{
  srand(time(NULL));
  Options::renderColliders = true;

  GameParams params = {(char*const)"game", 800, 600};
  Engine engine(params);

  // Coord system
  for (int i = 0; i <= 20; i++)
  {
    engine.createEntity<Point>(Vector{-500.0f + 50.0f * i, 0.0f});
    engine.createEntity<Point>(Vector{0.0f, -500.0f + 50.0f * i});
  }

  std::vector<Platform*> platforms;
  // platforms.reserve(10);
  // for (int i = 0; i < 10; i++) { platforms.push_back(engine.createEntity<Platform>()); }
  Player* player = engine.createEntity<Player>(platforms);

  for (int i = 0; i < 1; i++) { engine.createEntity<Enemy>(player); }

  return engine.start();
}
