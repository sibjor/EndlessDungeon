#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

extern SDL_Texture* texture;
extern SDL_Texture* floorTexture;
extern SDL_Texture* wallTextureNorth;
extern SDL_Texture* wallTextureSouth;
extern SDL_Texture* wallTextureEast;
extern SDL_Texture* wallTextureWest;
extern SDL_Texture* stairTexture;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
bool loadAllTextures(SDL_Renderer* renderer);
void destroyTextures();

#endif 