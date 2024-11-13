#include <iostream>

#include "engine.h"

class Player : public Entity {
public:
  void initialize() override {
    std::cout << "Player initialized!" << std::endl;
  }

  void update() override { std::cout << "Updating player." << std::endl; }
};

int main(int argc, char *argv[]) {
  Engine engine;
  Player player;
  engine.RegisterEntity(&player);
  return engine.Start();
}
