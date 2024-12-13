#include <SDL_scancode.h>
#include <unordered_map>

#include "static/inputs.h"

std::unordered_map<SDL_Scancode, bool> Inputs::currentKeyState;
std::unordered_map<SDL_Scancode, bool> Inputs::previousKeyState;

std::unordered_map<Uint8, bool> Inputs::currentMouseState;
std::unordered_map<Uint8, bool> Inputs::previousMouseState;

int Inputs::mouseX = 0;
int Inputs::mouseY = 0;
int Inputs::mouseDeltaX = 0;
int Inputs::mouseDeltaY = 0;

void Inputs::update() {
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

bool Inputs::isKeyPressed(SDL_Scancode key) {
  return currentKeyState[key] && !previousKeyState[key];
}

bool Inputs::isKeyReleased(SDL_Scancode key) {
  return !currentKeyState[key] && previousKeyState[key];
}

bool Inputs::isKeyHeld(SDL_Scancode key) { return currentKeyState[key]; }

bool Inputs::isMouseButtonPressed(Uint8 button) {
  return currentMouseState[button] && !previousMouseState[button];
}

bool Inputs::isMouseButtonReleased(Uint8 button) {
  return !currentMouseState[button] && previousMouseState[button];
}

bool Inputs::isMouseButtonHeld(Uint8 button) {
  return currentMouseState[button];
}

void Inputs::getMousePosition(int &x, int &y) {
  x = mouseX;
  y = mouseY;
}

void Inputs::getMouseDelta(int &dx, int &dy) {
  dx = mouseDeltaX;
  dy = mouseDeltaY;
}
