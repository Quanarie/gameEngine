#include <SDL.h>
#include <SDL_timer.h>
#include <iostream>
#include <memory>

#include "component/render/render.h"
#include "component/transform.h"
#include "engine.h"
#include "entity.h"

Engine::Engine(GameParams params)
    : window(nullptr), renderer(nullptr), game_is_running(false), entities(),
      params(params) {}

Engine::~Engine() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
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

  for (const auto &entity : entities) {
    entity->initialize();
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
      if (event.type == SDL_QUIT) {
        game_is_running = false;
      }
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
  for (const auto &entity : entities) {
    entity->update();
  }
}

void Engine::render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  for (const auto &entity : entities) {
    TransformComponent *transform = entity->getComponent<TransformComponent>();
    RenderComponent *render = entity->getComponent<RenderComponent>();
    if (!transform || !render) {
      continue;
    }
    render->render(renderer, transform);
  }
  SDL_RenderPresent(renderer);
}
