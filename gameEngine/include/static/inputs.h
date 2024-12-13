#ifndef INPUTS_H
#define INPUTS_H

#include <SDL.h>
#include <unordered_map>

class Inputs {
public:
  static void update();

  static bool isKeyPressed(SDL_Scancode key);
  static bool isKeyReleased(SDL_Scancode key);
  static bool isKeyHeld(SDL_Scancode key);

  static bool isMouseButtonPressed(Uint8 button);
  static bool isMouseButtonReleased(Uint8 button);
  static bool isMouseButtonHeld(Uint8 button);

  static void getMousePosition(int &x, int &y);
  static void getMouseDelta(int &dx, int &dy);

private:
  Inputs() = delete;

  static std::unordered_map<SDL_Scancode, bool> currentKeyState;
  static std::unordered_map<SDL_Scancode, bool> previousKeyState;

  static std::unordered_map<Uint8, bool> currentMouseState;
  static std::unordered_map<Uint8, bool> previousMouseState;

  static int mouseX, mouseY;
  static int mouseDeltaX, mouseDeltaY;
};

#endif // INPUTS_H
