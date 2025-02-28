#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "slicer.h"

std::vector<std::string> findAssetDirectory(const std::string& startDir, const std::string& rootDir, const std::string& assetDir) {
    std::vector<std::string> assetFiles;
    std::filesystem::path currentPath = std::filesystem::absolute(startDir);

    // Search upwards for the root directory
    while (currentPath != currentPath.root_path()) {
        if (currentPath.filename() == rootDir) {
            std::cout << "Found root directory: " << currentPath << std::endl;
            break;
        }
        currentPath = currentPath.parent_path();
    }

    if (currentPath.filename() != rootDir) {
        std::cerr << "Root directory not found." << std::endl;
        return assetFiles;
    }

    // Search for the asset directory directly under the root directory
    std::filesystem::path assetPath = currentPath / assetDir;
    if (!std::filesystem::exists(assetPath) || !std::filesystem::is_directory(assetPath)) {
        std::cerr << "Assets directory not found in root directory." << std::endl;
        return assetFiles;
    }

    // Search for all .png files in the assets directory and its subdirectories
    try {
        std::cout << "Searching for .png files in assets directory: " << assetPath << std::endl;
        for (const auto& file : std::filesystem::recursive_directory_iterator(assetPath)) {
            if (file.path().extension() == ".png") {
                assetFiles.push_back(file.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return assetFiles;
}

void sliceSpritesheet(const std::vector<std::string>& assetFiles, int spriteWidth, int spriteHeight, const std::string& outputDir) {
    for (const auto& assetFile : assetFiles) {
        SDL_Surface* image = IMG_Load(assetFile.c_str());
        if (!image) {
            SDL_Log("Unable to load image: %s", SDL_GetError());
            continue;
        }

        int rows = image->h / spriteHeight;
        int cols = image->w / spriteWidth;

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                SDL_Rect srcRect = { x * spriteWidth, y * spriteHeight, spriteWidth, spriteHeight };
                SDL_Surface* sprite = SDL_CreateSurface(spriteWidth, spriteHeight, SDL_PIXELFORMAT_RGBA32);
                SDL_BlitSurface(image, &srcRect, sprite, NULL);

                // Save each sprite to a file in the output directory
                std::string outputPath = outputDir + "/sprite_" + std::to_string(y) + "_" + std::to_string(x) + ".png";
                IMG_SavePNG(sprite, outputPath.c_str());
                SDL_DestroySurface(sprite);
            }
        }

        SDL_DestroySurface(image);
    }
}