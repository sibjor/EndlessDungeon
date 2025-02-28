#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);

#endif 