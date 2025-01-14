#include <SDL.h>
#include <iostream>

#include "engine.h"

#include <thread>

#include "entity.h"
#include "static/inputs.h"
#include "static/options.h"
#include "static/coordinates_converter.h"
#include "component/transform_component.h"
#include "static/texture_manager.h"
#include "component/render/render_component.h"
#include "component/collider/collider_component.h"

Engine::Engine(GameParams params)
  : params(params), window(nullptr), renderer(nullptr), game_is_running(false)
{
  CoordinatesConverter::setResolution(params.resolutionX, params.resolutionY);

  scenes[DEFAULT_SCENE_NAME] = Scene{};
  currentScene = DEFAULT_SCENE_NAME;
}

Engine::~Engine()
{
  for (auto scenePair : scenes)
    for (Entity* entity : scenePair.second.entities) { delete entity; }

  TextureManager::clear();

  if (renderer) SDL_DestroyRenderer(renderer);
  if (window) SDL_DestroyWindow(window);
  SDL_Quit();
}

void Engine::addScene(const std::string& name) { if (!scenes.contains(name)) { scenes[name] = Scene{}; } }

void Engine::changeScene(const std::string& name, const std::vector<Entity*>& entitiesToAddToNewScene)
{
  if (!scenes.contains(name)) { throw std::runtime_error("Scene not found: " + name); }

  auto& targetSceneEntities = scenes[name].entities;

  targetSceneEntities.reserve(targetSceneEntities.size() + entitiesToAddToNewScene.size());

  for (Entity* entity : entitiesToAddToNewScene)
  {
    if (!entity || std::ranges::find(targetSceneEntities, entity) != targetSceneEntities.end())
      continue;

    targetSceneEntities.push_back(entity);

    // TODO think about deleting them from prev scene. Maybe it makes sense in some cases
    // auto it = std::ranges::find(currentSceneEntities, entity);
    // if (it != currentSceneEntities.end()) { currentSceneEntities.erase(it); }
  }

  currentScene = name;
}

void Engine::addEntity(std::string sceneName, Entity* entity)
{
  if (!scenes.contains(sceneName)) { addScene(sceneName); }
  scenes[sceneName].entities.push_back(entity);
}

int Engine::start()
{
  if (!initialize())
  {
    std::cerr << "Failed to initialize!" << std::endl;
    return 1;
  }

  loop();
  return 0;
}

bool Engine::initialize()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
      << std::endl;
    return false;
  }

  window = SDL_CreateWindow(params.window_title, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, params.resolutionX,
                            params.resolutionY, SDL_WINDOW_SHOWN);
  if (!window)
  {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
      << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
  {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
      << std::endl;
    return false;
  }

  TextureManager::initialize(renderer);

  for (const auto& entity : getEntities())
  {
    entity->initialize();

    auto components = entity->getAllComponents();
    for (const auto& component : components) { component->initialize(); }

    auto collider = entity->getComponent<ColliderComponent>();
    if (collider)
    {
      // TODO: This is duplicated logic from addComponent in Entity
      collider->colliderBoundsRenderComponent->entity = entity;
      collider->colliderBoundsRenderComponent->initialize();
    }
  }

  return true;
}

void Engine::loop()
{
  using Clock = std::chrono::high_resolution_clock;
  using TimePoint = std::chrono::time_point<Clock>;
  using Milliseconds = std::chrono::milliseconds;

  const int targetFPS = 60;
  const Milliseconds frameDuration(1000 / targetFPS);

  game_is_running = true;
  while (game_is_running)
  {
    TimePoint frameStart = Clock::now();

    SDL_Event event;
    while (SDL_PollEvent(&event)) { if (event.type == SDL_QUIT) { game_is_running = false; } }

    update();
    render();

    TimePoint frameEnd = Clock::now();
    auto frameTime = std::chrono::duration_cast<Milliseconds>(frameEnd - frameStart);
    std::cout << frameTime.count() << " frameLength" << std::endl;

    // Delay if the frame finished early, it's an upper bound for fps, TODO: add lower bound
    if (frameTime < frameDuration) { std::this_thread::sleep_for(frameDuration - frameTime); }
  }
}

void Engine::update()
{
  Inputs::update();
  for (const auto& entity : getEntities())
  {
    auto col = entity->getComponent<ColliderComponent>();
    auto trans = entity->getComponent<TransformComponent>();
    if (col && trans) { col->prevPos = trans->pos; }
    entity->update();
  }
  resolveCollisions();
}

void Engine::resolveCollisions()
{
  for (size_t i = 0; i < getEntities().size(); ++i)
  {
    auto colliderA = getEntities()[i]->getComponent<ColliderComponent>();
    if (!colliderA)
      continue;
    // TODO: change checking every pair
    for (size_t j = i + 1; j < getEntities().size(); ++j)
    {
      auto colliderB =
        getEntities()[j]->getComponent<ColliderComponent>();
      if (!colliderB)
        continue;
      if (colliderA->resolve(*colliderB))
      {
        getEntities()[i]->onCollision(colliderB);
        getEntities()[j]->onCollision(colliderA);
      }
    }
  }
}

void Engine::render()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  for (const auto& entity : getEntities())
  {
    auto transform = entity->getComponent<TransformComponent>();
    auto render = entity->getComponent<RenderComponent>();
    if (transform && render)
      render->render(renderer);

    auto collider = entity->getComponent<ColliderComponent>();
    if (collider && Options::renderColliders)
      collider->render(renderer);
  }
  SDL_RenderPresent(renderer);
}
