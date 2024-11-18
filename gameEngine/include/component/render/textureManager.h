#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <memory>
#include <string>
#include <unordered_map>

struct SDL_Texture_Deleter {
  void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};

class TextureManager {
public:
  static bool has(const std::string &path);
  static void create(const std::string &path, SDL_Renderer *renderer);
  static SDL_Texture *get(const std::string &path);
  static void clear();

private:
  TextureManager() = delete;

  static std::unordered_map<std::string,
                            std::unique_ptr<SDL_Texture, SDL_Texture_Deleter>>
      textures;
  static SDL_Texture *loadTexture(const std::string &path,
                                  SDL_Renderer *renderer);
};

#endif // TEXTURE_MANAGER_H
