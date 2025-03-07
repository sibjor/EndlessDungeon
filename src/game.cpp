#include "game.h"

Game::Game()
{
    // Constructor implementation

    // If no save data exists
    if (!SaveData::saveFiles.size() > 0){
        // Create a save file
        SaveData::saveFiles.push_back(1);
        // Add metadata to save file (not implemented)
        // Create the first floor
        Dungeon firstFloor = Dungeon();
        dungeons.push_back(firstFloor);
    }
}
