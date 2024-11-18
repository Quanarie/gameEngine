#include <SDL_scancode.h>
#include <unordered_map>

#include "inputs.h"

std::unordered_map<SDL_Scancode, bool> Inputs::currentKeyState;
std::unordered_map<SDL_Scancode, bool> Inputs::previousKeyState;

std::unordered_map<Uint8, bool> Inputs::currentMouseState;
std::unordered_map<Uint8, bool> Inputs::previousMouseState;

int Inputs::mouseX = 0;
int Inputs::mouseY = 0;
int Inputs::mouseDeltaX = 0;
int Inputs::mouseDeltaY = 0;

void Inputs::Initialize() {
  SDL_GetMouseState(&mouseX, &mouseY);
  mouseDeltaX = mouseDeltaY = 0;
}

void Inputs::Update() {
  previousKeyState = currentKeyState;
  previousMouseState = currentMouseState;

  const Uint8 *keyboardState = SDL_GetKeyboardState(nullptr);
  for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
    currentKeyState[static_cast<SDL_Scancode>(i)] = keyboardState[i];
  }

  int newMouseX, newMouseY;
  Uint32 mouseState = SDL_GetMouseState(&newMouseX, &newMouseY);
  mouseDeltaX = newMouseX - mouseX;
  mouseDeltaY = newMouseY - mouseY;
  mouseX = newMouseX;
  mouseY = newMouseY;

  currentMouseState[SDL_BUTTON_LEFT] = mouseState & SDL_BUTTON(SDL_BUTTON_LEFT);
  currentMouseState[SDL_BUTTON_RIGHT] =
      mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT);
  currentMouseState[SDL_BUTTON_MIDDLE] =
      mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE);
}

void Inputs::Shutdown() {
  currentKeyState.clear();
  previousKeyState.clear();
  currentMouseState.clear();
  previousMouseState.clear();
}

bool Inputs::IsKeyPressed(SDL_Scancode key) {
  return currentKeyState[key] && !previousKeyState[key];
}

bool Inputs::IsKeyReleased(SDL_Scancode key) {
  return !currentKeyState[key] && previousKeyState[key];
}

bool Inputs::IsKeyHeld(SDL_Scancode key) { return currentKeyState[key]; }

bool Inputs::IsMouseButtonPressed(Uint8 button) {
  return currentMouseState[button] && !previousMouseState[button];
}

bool Inputs::IsMouseButtonReleased(Uint8 button) {
  return !currentMouseState[button] && previousMouseState[button];
}

bool Inputs::IsMouseButtonHeld(Uint8 button) {
  return currentMouseState[button];
}

void Inputs::GetMousePosition(int &x, int &y) {
  x = mouseX;
  y = mouseY;
}

void Inputs::GetMouseDelta(int &dx, int &dy) {
  dx = mouseDeltaX;
  dy = mouseDeltaY;
}
