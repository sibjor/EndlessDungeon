#include "texture_loader.h"

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (!newTexture) {
        SDL_Log("Failed to load texture: %s\n", SDL_GetError());
    }
    return newTexture;
}