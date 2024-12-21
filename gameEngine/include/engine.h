#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <vector>

class Entity;

typedef struct GameParams {
  char* window_title;
  int resolutionX;
  int resolutionY;
} GameParams;

// TODO: singleton?
class Engine {
public:
  Engine(GameParams params);
  ~Engine();

  int start();

  // Arguments go to entities constructor
  template <typename T, typename... Args>
  T* createEntity(Args&&... args) {
    T* entity = new T(std::forward<Args>(args)...);
    entities.push_back(entity);
    return entity;
  }

private:
  bool initialize();
  void loop();
  void update();
  void resolveCollisions();
  void render();

  static constexpr int TICKS_PER_SECOND = 60;
  static constexpr int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
  static constexpr int MAX_FRAMESKIP = 10;

  GameParams params;

  SDL_Window* window;
  SDL_Renderer* renderer;

  std::vector<Entity*> entities;

  bool game_is_running;
};

#endif // ENGINE_H
