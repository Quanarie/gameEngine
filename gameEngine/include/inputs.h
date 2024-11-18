#ifndef INPUTS_H
#define INPUTS_H

#include <SDL.h>
#include <unordered_map>

class Inputs {
public:
  static void Initialize();
  static void Update();
  static void Shutdown();

  static bool IsKeyPressed(SDL_Scancode key);
  static bool IsKeyReleased(SDL_Scancode key);
  static bool IsKeyHeld(SDL_Scancode key);

  static bool IsMouseButtonPressed(Uint8 button);
  static bool IsMouseButtonReleased(Uint8 button);
  static bool IsMouseButtonHeld(Uint8 button);

  static void GetMousePosition(int &x, int &y);
  static void GetMouseDelta(int &dx, int &dy);

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
