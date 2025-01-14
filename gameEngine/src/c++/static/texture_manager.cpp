#include <SDL_render.h>
#include <SDL_surface.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "static/texture_manager.h"

// Debugging
void TextureManager::printInfo()
{
  std::cout << "Printing info: " << std::endl;
  for (auto texture : textures) { std::cout << texture.first << std::endl; }
}

std::unordered_map<std::string, SDL_Texture*> TextureManager::textures;
SDL_Renderer* TextureManager::renderer = nullptr;

void TextureManager::initialize(SDL_Renderer* renderer) { TextureManager::renderer = renderer; }

bool TextureManager::has(const std::string& path) { return textures.contains(path); }

void TextureManager::create(const std::string& path)
{
  if (has(path) || path.empty()) { return; }

  SDL_Texture* texture = loadTexture(path, renderer);
  if (!texture) { std::cerr << "Failed to load texture: " + path << std::endl; }
  else { textures[path] = texture; }
}

SDL_Texture* TextureManager::get(const std::string& path)
{
  // TODO thrown randomly sometimes
  if (!has(path))
  {
    printInfo();
    throw std::runtime_error("Texture not found: " + path);
  }
  return textures[path];
}

SDL_Texture* TextureManager::loadTexture(const std::string& path,
                                         SDL_Renderer* renderer)
{
  std::cout << "Attempting to load BMP from: " << path.c_str() << std::endl;
  SDL_Surface* surface = SDL_LoadBMP(path.data());
  if (!surface)
  {
    std::cerr << "Failed to load BMP: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!texture)
  {
    std::cerr << "Failed to create texture from surface: " << SDL_GetError()
      << std::endl;
  }

  return texture;
}

void TextureManager::clear()
{
  for (auto& pair : textures) { SDL_DestroyTexture(pair.second); }
  textures.clear();
}
