#include "component/transform.h"
#include "engine.h"

class Player : public Entity {
public:
  void initialize() override {
    transform =
        addComponent<TransformComponent>(100.0f, 200.0f, 45.0f, 1.0f, 1.0f);
  }
  void update() override { transform->y -= 0.1; }

private:
  TransformComponent *transform;
};

int main(int argc, char *argv[]) {
  Engine engine;
  Player player;
  engine.registerEntity(&player);
  return engine.start();
}
