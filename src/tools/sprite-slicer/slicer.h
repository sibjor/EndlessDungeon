#ifndef SLICER_H
#define SLICER_H

#include <string>
#include <vector>

void sliceSpritesheet(const std::string& assetFile, int spriteWidth, int spriteHeight, const std::string& outputDir);
bool compareSurfaces(SDL_Surface* surface1, SDL_Surface* surface2);

#endif // SLICER_H