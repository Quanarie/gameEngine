#include "component/collider/polygonCollider.h"
#include "component/render/ellipseRender.h"
#include "component/transform.h"
#include "engine.h"
#include "entity.h"
#include <initializer_list>

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
    transform->point.x += rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1);
    transform->point.y += rand() % 10 / 5.0 * (rand() % 2 == 0 ? 1 : -1);
  }

private:
  TransformComponent *transform;
  EllipseRenderComponent *render;
  PolygonColliderComponent *collider;
};

int main(int argc, char *argv[]) {
  GameParams params = {(char *const)"game", 800, 600};
  Engine engine(params);

  for (int i = 0; i < 20; i++) {
    engine.createEntity<Player>();
  }

  return engine.start();
}
