#include "slicer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <sys/stat.h>
#include <sys/types.h>

int compareSurfaces(SDL_Surface* surface1, SDL_Surface* surface2) {
    if (surface1->w != surface2->w || surface1->h != surface2->h) {
        return 0;
    }

    int pitch1 = surface1->pitch;
    int pitch2 = surface2->pitch;
    Uint8* pixels1 = (Uint8*)surface1->pixels;
    Uint8* pixels2 = (Uint8*)surface2->pixels;

    for (int y = 0; y < surface1->h; ++y) {
        if (memcmp(pixels1 + y * pitch1, pixels2 + y * pitch2, pitch1) != 0) {
            return 0;
        }
    }

    return 1;
}

void sliceSpritesheet(const char* assetFile, int spriteWidth, int spriteHeight, const char* outputDir) {
    SDL_Surface* image = IMG_Load(assetFile);
    if (!image) {
        SDL_Log("Unable to load image: %s", SDL_GetError());
        return;
    }

    int rows = image->h / spriteHeight;
    int cols = image->w / spriteWidth;

    // Create the output directory if it doesn't exist
    mkdir(outputDir, 0777);

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            SDL_Rect srcRect = { x * spriteWidth, y * spriteHeight, spriteWidth, spriteHeight };
            SDL_Surface* sprite = SDL_CreateRGBSurfaceWithFormat(0, spriteWidth, spriteHeight, 32, SDL_PIXELFORMAT_RGBA32);
            SDL_BlitSurface(image, &srcRect, sprite, NULL);

            // Save each sprite to a file in the output directory
            char outputPath[256];
            snprintf(outputPath, sizeof(outputPath), "%s/sprite_%d_%d.png", outputDir, y, x);

            // Check if the file already exists and is identical
            if (access(outputPath, F_OK) == 0) {
                SDL_Surface* existingSprite = IMG_Load(outputPath);
                if (existingSprite && compareSurfaces(sprite, existingSprite)) {
                    SDL_Log("Sprite %s already exists and is identical. Skipping export.", outputPath);
                    SDL_FreeSurface(existingSprite);
                    SDL_FreeSurface(sprite);
                    continue;
                }
                SDL_FreeSurface(existingSprite);
            }

            IMG_SavePNG(sprite, outputPath);
            SDL_FreeSurface(sprite);
        }
    }

    SDL_FreeSurface(image);
}