#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "tools/sprite-slicer/slicer.h"
#include "dungeon_generator.h"
#include "tools/file_utils.h"  // Include the file_utils.h header

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static SDL_Texture *floorTexture = NULL;
static SDL_Texture *wallTextureNorth = NULL;
static SDL_Texture *wallTextureSouth = NULL;
static SDL_Texture *wallTextureEast = NULL;
static SDL_Texture *wallTextureWest = NULL;

SDL_Texture* loadTexture(const std::string& path) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (!newTexture) {
        SDL_Log("Failed to load texture: %s\n", SDL_GetError());
    }
    return newTexture;
}

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Find the specific asset file
    std::string assetFile = findAssetFile("EndlessDungeon", "assets", "Dungeon_Tileset.png");

    // Slice the spritesheet with 16px size
    if (!assetFile.empty()) {
        sliceSpritesheet(assetFile, 16, 16, "assets/sliced_sprites"); // Slice sprites with 16x16 size and export to "assets/sliced_sprites" directory
        texture = IMG_LoadTexture(renderer, assetFile.c_str());
        if (!texture) {
            SDL_Log("Couldn't load texture: %s\n", SDL_GetError());
            return SDL_APP_FAILURE;
        }
    } else {
        SDL_Log("Asset file not found in the directory.");
        return SDL_APP_FAILURE;
    }

    // Load textures
    floorTexture = loadTexture("assets/sliced_sprites/sprite_0_0.png");
    wallTextureNorth = loadTexture("assets/sliced_sprites/sprite_0_1.png");
    wallTextureSouth = loadTexture("assets/sliced_sprites/sprite_0_2.png");
    wallTextureEast = loadTexture("assets/sliced_sprites/sprite_0_3.png");
    wallTextureWest = loadTexture("assets/sliced_sprites/sprite_0_4.png");

    if (!floorTexture || !wallTextureNorth || !wallTextureSouth || !wallTextureEast || !wallTextureWest) {
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    int w = 0, h = 0;
    SDL_FRect dst;
    const float scale = 4.0f;

    /* Center the icon and scale it up */
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    SDL_GetTextureSize(texture, &dst.w, &dst.h);
    dst.x = ((w / scale) - dst.w) / 2;
    dst.y = ((h / scale) - dst.h) / 2;

    /* Draw the icon */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, &dst);

    // Render the dungeon
    auto dungeon = generateDungeon();
    int tileSize = 16;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            SDL_FRect dstRect = { static_cast<float>(x * tileSize), static_cast<float>(y * tileSize), static_cast<float>(tileSize), static_cast<float>(tileSize) };
            if (dungeon[y][x] == FLOOR) {
                SDL_RenderTexture(renderer, floorTexture, NULL, &dstRect);
            } else if (dungeon[y][x] == WALL) {
                // Determine which wall texture to use based on surrounding tiles
                if (y > 0 && dungeon[y - 1][x] == FLOOR) {
                    SDL_RenderTexture(renderer, wallTextureNorth, NULL, &dstRect);
                } else if (y < HEIGHT - 1 && dungeon[y + 1][x] == FLOOR) {
                    SDL_RenderTexture(renderer, wallTextureSouth, NULL, &dstRect);
                } else if (x > 0 && dungeon[y][x - 1] == FLOOR) {
                    SDL_RenderTexture(renderer, wallTextureWest, NULL, &dstRect);
                } else if (x < WIDTH - 1 && dungeon[y][x + 1] == FLOOR) {
                    SDL_RenderTexture(renderer, wallTextureEast, NULL, &dstRect);
                } else {
                    SDL_RenderTexture(renderer, wallTextureNorth, NULL, &dstRect); // Default to north wall
                }
            }
        }
    }

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyTexture(floorTexture);
    SDL_DestroyTexture(wallTextureNorth);
    SDL_DestroyTexture(wallTextureSouth);
    SDL_DestroyTexture(wallTextureEast);
    SDL_DestroyTexture(wallTextureWest);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}