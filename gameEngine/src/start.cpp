#include <SDL.h>
#include <SDL_timer.h>
#include <iostream>

#include "init/start.h"

#define TICKS_PER_SECOND 50
#define SKIP_TICKS 1000 / TICKS_PER_SECOND
#define MAX_FRAMESKIP 10

bool initialize(SDL_Window **window, SDL_Renderer **renderer);
void main_loop();
void update_game();
void display_game();
void cleanup(SDL_Window *window, SDL_Renderer *renderer);

int start() {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  if (!initialize(&window, &renderer)) {
    std::cerr << "Failed to initialize!" << std::endl;
    return 1;
  }

  main_loop();
  cleanup(window, renderer);
  return 0;
}

bool initialize(SDL_Window **window, SDL_Renderer **renderer) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  *window =
      SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
  if (!*window) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
  if (!*renderer) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  return true;
}

void main_loop() {
  Uint32 next_game_tick = SDL_GetTicks();
  int loops;

  bool game_is_running = true;
  while (game_is_running) {
    loops = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        game_is_running = false;
      }
    }

    while (SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
      update_game();

      next_game_tick += SKIP_TICKS;
      loops++;
    }

    display_game();
  }
}

void update_game() {
  //    cout << "U" << std::endl;
}

void display_game() {
  //    cout << "D" << std::endl;
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
