#include "texture_loader.h"

SDL_Texture* texture = NULL;
SDL_Texture* floorTexture = NULL;
SDL_Texture* wallTextureNorth = NULL;
SDL_Texture* wallTextureSouth = NULL;
SDL_Texture* wallTextureEast = NULL;
SDL_Texture* wallTextureWest = NULL;
SDL_Texture* stairTexture = NULL;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (!newTexture) {
        SDL_Log("Failed to load texture: %s\n", SDL_GetError());
    }
    return newTexture;
}

bool loadAllTextures(SDL_Renderer* renderer) {
    floorTexture = loadTexture(renderer, "../../assets/use/floor.png");
    wallTextureNorth = loadTexture(renderer, "../../assets/use/wall_north.png");
    wallTextureSouth = loadTexture(renderer, "../../assets/use/wall_south.png");
    wallTextureEast = loadTexture(renderer, "../../assets/use/wall_east.png");
    wallTextureWest = loadTexture(renderer, "../../assets/use/wall_west.png");
    stairTexture = loadTexture(renderer, "../../assets/use/stair.png");

    if (!floorTexture || !wallTextureNorth || !wallTextureSouth || !wallTextureEast || !wallTextureWest || !stairTexture) {
        return false;
    }
    return true;
}

void destroyTextures(){
    SDL_DestroyTexture(floorTexture);
    SDL_DestroyTexture(wallTextureNorth);
    SDL_DestroyTexture(wallTextureSouth);
    SDL_DestroyTexture(wallTextureEast);
    SDL_DestroyTexture(wallTextureWest);
    SDL_DestroyTexture(stairTexture);
}