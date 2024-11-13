#include <SDL.h>
#include <SDL_timer.h>
#include <iostream>

#include "engine.h"
#include "entity.h"

Engine::Engine()
    : window(nullptr), renderer(nullptr), game_is_running(false), entities() {}

Engine::~Engine() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int Engine::Start() {
  if (!initialize()) {
    std::cerr << "Failed to initialize!" << std::endl;
    return 1;
  }

  loop();
  return 0;
}

void Engine::RegisterEntity(Entity *entity) { entities.push_back(entity); }

bool Engine::initialize() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  window = SDL_CreateWindow("gameEngine", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
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

  for (Entity *entity : entities) {
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
  for (Entity *entity : entities) {
    entity->update();
  }

  std::cout << "Current entities count" << entities.size() << std::endl;
}

void Engine::render() {}
