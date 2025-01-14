#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <SDL.h>
#include <vector>

#define DEFAULT_SCENE_NAME "default"

class Entity;

typedef struct GameParams
{
  char* window_title;
  int resolutionX;
  int resolutionY;
} GameParams;

struct Scene
{
  std::vector<Entity*> entities{};
};

// TODO: singleton?
class Engine
{
public:
  Engine(GameParams params);
  ~Engine();

  int start();
  void addScene(const std::string& name);
  void changeScene(const std::string& name, const std::vector<Entity*>& entitiesToAddToNewScene);

  // Arguments go to entities constructor
  template <typename T, typename... Args>
  T* createEntity(const std::string& sceneName, Args&&... args)
  {
    T* entity = new T(std::forward<Args>(args)...);
    addEntity(sceneName, entity);
    return entity;
  }

private:
  bool initialize();
  void loop();
  void update();
  void resolveCollisions();
  void render();
  std::vector<Entity*>& getEntities() { return scenes[currentScene].entities; }
  void addEntity(std::string sceneName, Entity* entity);

  GameParams params;

  SDL_Window* window;
  SDL_Renderer* renderer;

  std::string currentScene;
  std::map<std::string, Scene> scenes;

  bool game_is_running;
};

#endif // ENGINE_H
