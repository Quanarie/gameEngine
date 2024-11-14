#include "component/transform.h"
#include "engine.h"
#include "entity.h"

class Player : public Entity {
public:
  void initialize() override {
    transform =
        addComponent<TransformComponent>(400.0f, 300.0f, 0.0f, 1.0f, 1.0f);
  }
  void update() override {
    transform->x += rand() % 10 / 10.0 * (rand() % 2 == 0 ? 1 : -1);
    transform->y += rand() % 10 / 10.0 * (rand() % 2 == 0 ? 1 : -1);
  }

private:
  TransformComponent *transform;
};

int main(int argc, char *argv[]) {
  GameParams params = {(char *const)"game", 800, 600};
  Engine engine(params);

  for (int i = 0; i < 100000; i++) {
    engine.createEntity<Player>();
  }

  return engine.start();
}
