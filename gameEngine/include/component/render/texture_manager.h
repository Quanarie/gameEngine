#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <string>
#include <unordered_map>

class TextureManager {
public:
  static bool has(const std::string& path);
  static void create(const std::string& path, SDL_Renderer* renderer);
  static SDL_Texture* get(const std::string& path);
  static void clear();

private:
  TextureManager() = delete;

  static SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);

  static std::unordered_map<std::string, SDL_Texture*> textures;
};

#endif // TEXTURE_MANAGER_H
