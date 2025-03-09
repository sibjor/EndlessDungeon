/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() for web compatibility */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

struct TextureInfo {
    SDL_Texture* texture;
    SDL_FRect position;
};

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static std::vector<TextureInfo> textures = {
    
};

const int tileSize = 16; // Assuming each texture is 16x16 pixels
const float padding = 2.0f; // Padding between tiles
const int mapWidth = tileSize * 26;
const int mapHeight = tileSize * 21;

/* List of hard-coded asset file paths */
std::vector<std::string> assetFiles = {
    "Debug/assets/chest.png",
    "Debug/assets/door_left.png",
    "Debug/assets/door_left2.png",
    "Debug/assets/door_right.png",
    "Debug/assets/door_right2.png",
    "Debug/assets/floor.png",
    "Debug/assets/key.png",
    "Debug/assets/key2.png",
    "Debug/assets/stair.png",
    "Debug/assets/wall_east.png",
    "Debug/assets/wall_north.png",
    "Debug/assets/wall_south.png",
    "Debug/assets/wall_west.png",
    // Add more file paths as needed
};

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("EndlessDungeon", 1280, 1024, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    /*  Load each texture from the specified file paths 
        Next steps: Generate procedually possibly with if - statements
        Those if:s (or switch) could verify adjacent tiles
        A min-max value of certain adjacent tile type:s (textures)
        - could set an un-symmetrical dungeon generation
        - with the walls always on the end, stair minimum 2 etc*/
    for (const std::string& filePath : assetFiles) { // Range-based for loop
        TextureInfo texInfo;
        texInfo.texture = IMG_LoadTexture(renderer, filePath.c_str());
        if (!texInfo.texture) {
            SDL_Log("Couldn't load texture %s: %s\n", filePath.c_str(), SDL_GetError());
            return SDL_APP_FAILURE;
        }
        texInfo.position = {0, 0, 0, 0}; // Initialize position, this will be generated procedurally
        textures.push_back(texInfo);
    }

    /* Seed the random number generator */
    std::srand(std::time(nullptr));

    /* Generate the dungeon map */
    GenerateDungeonMap();

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
    const float scale = 1.0f;

    /* Clear the screen */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    /* Render each texture */
    for (TextureInfo& texInfo : textures) {
        SDL_SetRenderScale(renderer, scale, scale);
        SDL_RenderTexture(renderer, texInfo.texture, NULL, &texInfo.position);
    }

    /* Present the renderer */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    for (TextureInfo& texInfo : textures) {
        SDL_DestroyTexture(texInfo.texture);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

/* Function to generate the dungeon map */
void GenerateDungeonMap()
{
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int tileIndex = std::rand() % textures.size();
            SDL_FRect position = { x * tileSize + padding, y * tileSize + padding, tileSize, tileSize };
            textures[tileIndex].position = position;
        }
    }
}