#include <SDL.h>
#include <SDL_timer.h>
#include <iostream>

#include "component/collider/collider_component.h"
#include "component/render/render_component.h"
#include "component/render/texture_manager.h"
#include "component/transform_component.h"
#include "engine.h"
#include "entity.h"
#include "inputs.h"
#include "options.h"

Engine::Engine(GameParams params)
  : params(params), window(nullptr), renderer(nullptr), game_is_running(false) {}

Engine::~Engine() {
  for (Entity* entity : entities) {
    delete entity;
  }

  TextureManager::clear();

  if (renderer) SDL_DestroyRenderer(renderer);
  if (window) SDL_DestroyWindow(window);
  SDL_Quit();
}

int Engine::start() {
  if (!initialize()) {
    std::cerr << "Failed to initialize!" << std::endl;
    return 1;
  }

  loop();
  return 0;
}

bool Engine::initialize() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
      << std::endl;
    return false;
  }

  window = SDL_CreateWindow(params.window_title, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, params.resolution_x,
                            params.resolution_y, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
      << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
      << std::endl;
    return false;
  }

  for (const auto& entity : entities) {
    entity->initialize();

    auto render = entity->getComponent<RenderComponent>();
    if (!render)
      continue;

    render->initialize(renderer);
  }

  return true;
}

void Engine::loop() {
  Uint32 next_game_tick = SDL_GetTicks();
  int loops;

  game_is_running = true;
  while (game_is_running) {
    loops = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) { game_is_running = false; }
    }

    while (SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
      update();

      next_game_tick += SKIP_TICKS;
      loops++;
    }

    render();
  }
}

void Engine::update() {
  Inputs::update();
  for (const auto& entity : entities) { entity->update(); }
  detectCollisions();
}

void Engine::detectCollisions() {
  for (size_t i = 0; i < entities.size(); ++i) {
    auto colliderA = entities[i]->getComponent<ColliderComponent>();
    auto transformA = entities[i]->getComponent<TransformComponent>();
    if (!colliderA || !transformA)
      continue;

    // TODO: change checking every pair
    for (size_t j = i + 1; j < entities.size(); ++j) {
      auto colliderB =
        entities[j]->getComponent<ColliderComponent>();
      auto transformB = entities[j]->getComponent<TransformComponent>();
      if (!colliderB || !transformB)
        continue;
      if (colliderA->detect(*colliderB, *transformA, *transformB)) {
        std::cout << colliderA << " is colliding with " << colliderB << " " <<
          rand() << std::endl;
      }
    }
  }
}

void Engine::render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  for (const auto& entity : entities) {
    auto transform = entity->getComponent<TransformComponent>();
    auto render = entity->getComponent<RenderComponent>();
    if (transform && render)
      render->render(renderer, transform);

    auto collider = entity->getComponent<ColliderComponent>();
    if (collider && Options::renderColliders)
      collider->render(renderer, transform);
  }
  SDL_RenderPresent(renderer);
}
