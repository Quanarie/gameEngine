#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <entity.h>
#include <vector>

class Engine {
public:
  Engine();
  ~Engine();

  int start();
  void registerEntity(Entity *entity);

private:
  bool initialize();
  void loop();
  void update();
  void render();

  static constexpr int TICKS_PER_SECOND = 50;
  static constexpr int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
  static constexpr int MAX_FRAMESKIP = 10;

  SDL_Window *window;
  SDL_Renderer *renderer;
  std::vector<Entity *> entities;
  bool game_is_running;
};

#endif // ENGINE_H
