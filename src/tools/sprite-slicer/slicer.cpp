#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "slicer.h"

std::string findAssetFile(const std::string& startDir, const std::string& rootDir, const std::string& assetDir, const std::string& fileName) {
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
        return "";
    }

    // Search for the asset directory directly under the root directory
    std::filesystem::path assetPath = currentPath / assetDir;
    if (!std::filesystem::exists(assetPath) || !std::filesystem::is_directory(assetPath)) {
        std::cerr << "Assets directory not found in root directory." << std::endl;
        return "";
    }

    // Search for the specific file in the assets directory and its subdirectories
    try {
        std::cout << "Searching for file " << fileName << " in assets directory: " << assetPath << std::endl;
        for (const auto& file : std::filesystem::recursive_directory_iterator(assetPath)) {
            if (file.path().filename() == fileName) {
                return file.path().string();
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return "";
}

bool compareSurfaces(SDL_Surface* surface1, SDL_Surface* surface2) {
    if (surface1->w != surface2->w || surface1->h != surface2->h) {
        return false;
    }

    int pitch1 = surface1->pitch;
    int pitch2 = surface2->pitch;
    Uint8* pixels1 = static_cast<Uint8*>(surface1->pixels);
    Uint8* pixels2 = static_cast<Uint8*>(surface2->pixels);

    for (int y = 0; y < surface1->h; ++y) {
        if (memcmp(pixels1 + y * pitch1, pixels2 + y * pitch2, pitch1) != 0) {
            return false;
        }
    }

    return true;
}

void sliceSpritesheet(const std::string& assetFile, int spriteWidth, int spriteHeight, const std::string& outputDir) {
    SDL_Surface* image = IMG_Load(assetFile.c_str());
    if (!image) {
        SDL_Log("Unable to load image: %s", SDL_GetError());
        return;
    }

    int rows = image->h / spriteHeight;
    int cols = image->w / spriteWidth;

    // Create the output directory if it doesn't exist
    std::filesystem::create_directories(outputDir);

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            SDL_Rect srcRect = { x * spriteWidth, y * spriteHeight, spriteWidth, spriteHeight };
            SDL_Surface* sprite = SDL_CreateSurface(spriteWidth, spriteHeight, SDL_PIXELFORMAT_RGBA32);
            SDL_BlitSurface(image, &srcRect, sprite, NULL);

            // Save each sprite to a file in the output directory
            std::string outputPath = outputDir + "/sprite_" + std::to_string(y) + "_" + std::to_string(x) + ".png";

            // Check if the file already exists and is identical
            if (std::filesystem::exists(outputPath)) {
                SDL_Surface* existingSprite = IMG_Load(outputPath.c_str());
                if (existingSprite && compareSurfaces(sprite, existingSprite)) {
                    SDL_Log("Sprite %s already exists and is identical. Skipping export.", outputPath.c_str());
                    SDL_DestroySurface(existingSprite);
                    SDL_DestroySurface(sprite);
                    continue;
                }
                SDL_DestroySurface(existingSprite);
            }

            IMG_SavePNG(sprite, outputPath.c_str());
            SDL_DestroySurface(sprite);
        }
    }

    SDL_DestroySurface(image);
}