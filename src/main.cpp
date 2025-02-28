#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "tools/sprite-slicer/slicer.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Find asset directory and get all .png files
    std::vector<std::string> assetFiles = findAssetDirectory(".", "EndlessDungeon", "assets");

    // Slice the spritesheet with 16px size
    if (!assetFiles.empty()) {
        sliceSpritesheet(assetFiles, 16, 16, "sliced_sprites"); // Slice sprites with 16x16 size and export to "sliced_sprites" directory
        texture = IMG_LoadTexture(renderer, assetFiles[0].c_str());
        if (!texture) {
            SDL_Log("Couldn't load texture: %s\n", SDL_GetError());
            return SDL_APP_FAILURE;
        }
    } else {
        SDL_Log("No assets found in the directory.");
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
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}