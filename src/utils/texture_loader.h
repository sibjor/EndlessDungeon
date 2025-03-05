#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

void loadTexture(const char* filename, SDL_Renderer* renderer, SDL_Texture** texture) {
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        std::cerr << "Error: Unable to load image " << filename << std::endl;
        return;
    }

    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!*texture) {
        std::cerr << "Error: Unable to create texture from surface." << std::endl;
        return;
    }
};

void destroyTexture(SDL_Texture* texture) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
};