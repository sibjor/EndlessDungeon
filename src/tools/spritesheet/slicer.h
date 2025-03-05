#ifndef SLICER_H
#define SLICER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

void sliceSpritesheet(const char* assetFile, int spriteWidth, int spriteHeight, const char* outputDir);
int compareSurfaces(SDL_Surface* surface1, SDL_Surface* surface2);

#endif // SLICER_H