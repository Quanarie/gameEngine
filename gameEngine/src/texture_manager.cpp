#include <SDL_render.h>
#include <SDL_surface.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "component/render/texture_manager.h"

std::unordered_map<std::string,
                   std::unique_ptr<SDL_Texture, SDL_Texture_Deleter>>
    TextureManager::textures{};

bool TextureManager::has(const std::string &path) {
  return textures.contains(path);
}

void TextureManager::create(const std::string &path, SDL_Renderer *renderer) {
  SDL_Texture *texture = loadTexture(path, renderer);
  if (!texture) {
    throw std::runtime_error("Failed to load texture: " + path);
  }

  textures[path] = std::unique_ptr<SDL_Texture, SDL_Texture_Deleter>(
      texture, SDL_Texture_Deleter());
}

SDL_Texture *TextureManager::get(const std::string &path) {
  if (!has(path)) {
    throw std::runtime_error("Texture not found: " + path);
  }
  return textures[path].get();
}

SDL_Texture *TextureManager::loadTexture(const std::string &path,
                                         SDL_Renderer *renderer) {
  std::cout << "Attempting to load BMP from: " << path << std::endl;
  SDL_Surface *surface = SDL_LoadBMP(path.c_str());
  if (!surface) {
    std::cerr << "Failed to load BMP: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!texture) {
    std::cerr << "Failed to create texture from surface: " << SDL_GetError()
              << std::endl;
  }

  return texture;
}