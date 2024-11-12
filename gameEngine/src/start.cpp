#include <SDL.h>
#include <SDL_timer.h>
#include <iostream>

#include "start.h"

using namespace std;


bool initialize(SDL_Window** window, SDL_Renderer** renderer);
void update_game();
void display_game();
void cleanup(SDL_Window* window, SDL_Renderer* renderer);

int start() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initialize(&window, &renderer)) {
        cerr << "Failed to initialize!" << endl;
        return 1;
    }
 
    const int TICKS_PER_SECOND = 50; 
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND; 
    const int MAX_FRAMESKIP = 10; 
 
    Uint32 next_game_tick = SDL_GetTicks();                        
    int loops; 
 
    bool game_is_running = true; 
    while(game_is_running) { 
	loops = 0;
	SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game_is_running = false;
            }
        }

	while(SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
            update_game(); 

            next_game_tick += SKIP_TICKS;
            loops++;
        }

        display_game();
    }

    cleanup(window, renderer);
    return 0;
}

bool initialize(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    *window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!*window) {
        cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void update_game() {
//    cout << "U" << endl;
}

void display_game() {
//    cout << "D" << endl;
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
