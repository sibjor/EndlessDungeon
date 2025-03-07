/*
    Here I want to implement separation of server logic and stuff to be run in the browser or client.
    This should prevent bugs with the browser trying to fetch files that are only available on the server.
*/

#ifndef SERVER_ONLY
#define SERVER_ONLY 0
#endif

#ifndef CLIENT_ONLY
#define CLIENT_ONLY 0
#endif

#define TRUE 1
#define FALSE 0

#define ASSETS_DIR "assets"
#define SPRITE_USE_PATH "assets/use"
#define WEB_BUILD_DIR "build-wasm"

#define CURRENT_PATH 1

#if SERVER_ONLY

#include "dir_utils.h"
#include "file_utils.h"
#include "slicer.h"

#endif // SERVER_ONLY

#if CLIENT_ONLY

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "dungeon_generator.h"
#include "texture_loader.h"

#endif

void displayCurrentPath();