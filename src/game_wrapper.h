#pragma once

#include "dungeon_generator.h"
#include "texture_loader.h"
#include "file_utils.h"
#include "dir_utils.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class GameWrapper{
    public:
        GameWrapper();
        ~GameWrapper();
        void Init();
        void Run();
        void Clean();
}