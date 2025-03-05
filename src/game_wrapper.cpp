#include "game_wrapper.h"

GameWrapper::GameWrapper(){
    // Constructor implementation
    GameWrapper::Init();
}

GameWrapper::~GameWrapper(){
    // Destructor implementation
    GameWrapper::Clean();
}

void GameWrapper::Init(){
    // Find project/root dir name
    DirUtils dirUtils;
    
    // Initialization implementation
    if (!SDL_CreateWindowAndRenderer(dirUtils.findProjectRoot(), 800, 600, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s\n", SDL_GetError());
        return;
    }

    // Load all textures
    if (!loadAllTextures(renderer)) {
        return;
    }

    // Generate initial dungeon
    dungeon = generateDungeon();
}

