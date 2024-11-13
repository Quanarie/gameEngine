#include "component/transform.h"
#include "engine.h"
#include "entity.h"

class Player : public Entity {
public:
  void initialize() override {
    transform =
        addComponent<TransformComponent>(400.0f, 300.0f, 0.0f, 1.0f, 1.0f);
  }
  void update() override { transform->y += 0.5f; }

private:
  TransformComponent *transform;
};

int main(int argc, char *argv[]) {
  GameParams params = {(char *const)"game", 800, 600};
  Engine engine(params);

  engine.createEntity<Player>();

  return engine.start();
}
