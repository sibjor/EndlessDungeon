#ifndef SLICER_H
#define SLICER_H

#include <string>
#include <vector>

std::vector<std::string> findAssetDirectory(const std::string& startDir, const std::string& rootDir, const std::string& assetDir);
void sliceSpritesheet(const std::vector<std::string>& assetFiles, int spriteWidth, int spriteHeight, const std::string& outputDir);

#endif // SLICER_H