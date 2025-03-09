/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <filesystem>
#include <vector>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static std::vector<SDL_Texture*> textures;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("EndlessDungeon", 800, 600, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* Load all PNG files from the assets directory */
    std::string basePath(SDL_GetBasePath());
    std::string assetsPath = basePath + "Debug/assets/";

    for (const auto &entry : std::filesystem::directory_iterator(assetsPath)) {
        if (entry.path().extension() == ".png") {
            SDL_Texture *tex = IMG_LoadTexture(renderer, entry.path().string().c_str());
            if (!tex) {
                SDL_Log("Couldn't load texture %s: %s\n", entry.path().string().c_str(), SDL_GetError());
                return SDL_APP_FAILURE;
            }
            textures.push_back(tex);
        }
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
    const float padding = 10.0f; // Padding between textures

    /* Clear the screen */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    /* Get the render output size */
    SDL_GetRenderOutputSize(renderer, &w, &h);

    /* Render each texture */
    float x = padding;
    float y = padding;
    for (SDL_Texture* tex : textures) {
        SDL_SetRenderScale(renderer, scale, scale);
        SDL_GetTextureSize(tex, &dst.w, &dst.h);
        dst.x = x;
        dst.y = y;

        /* Draw the texture */
        SDL_RenderTexture(renderer, tex, NULL, &dst);

        /* Update position for the next texture */
        x += dst.w + padding;
        if (x + dst.w + padding > w / scale) {
            x = padding;
            y += dst.h + padding;
        }
    }

    /* Present the renderer */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}