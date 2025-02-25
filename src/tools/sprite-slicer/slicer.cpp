#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

// Function declarations
std::vector<std::string> findAssetDirectory(const std::string& rootDir, const std::string& assetDir);
void sliceSpritesheet(const std::vector<std::string>& assetFiles, int spriteWidth, int spriteHeight, const std::string& outputDir);

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Find asset directory and get all .png files
    std::vector<std::string> assetFiles = findAssetDirectory("EndlessDungeon", "assets");

    // Example: Slice the assets found
    if (!assetFiles.empty()) {
        sliceSpritesheet(assetFiles, 32, 32, "output/directory"); // Example sprite size 32x32
    }

    SDL_Quit();
    return 0;
}

// Function to find the asset directory and return all .png files
std::vector<std::string> findAssetDirectory(const std::string& rootDir, const std::string& assetDir) {
    std::vector<std::string> assetFiles;
    // Search for the asset directory
    for (const auto& entry : std::filesystem::recursive_directory_iterator(rootDir)) {
        if (entry.is_directory() && entry.path().filename() == assetDir) {
            // If the asset directory is found, return all .png files in the directory and its subdirectories
            for (const auto& file : std::filesystem::recursive_directory_iterator(entry.path())) {
                if (file.path().extension() == ".png") {
                    assetFiles.push_back(file.path().string());
                }
            }
            break;
        }
    }
    return assetFiles;
}

// Function to slice the spritesheet into individual sprites
void sliceSpritesheet(const std::vector<std::string>& assetFiles, int spriteWidth, int spriteHeight, const std::string& outputDir) {
    for (const auto& assetFile : assetFiles) {
        SDL_Surface* image = IMG_Load(assetFile.c_str());
        if (!image) {
            SDL_Log("Unable to load image: %s", SDL_GetError());
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