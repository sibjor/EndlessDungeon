#include "game.h"

Game::Game() {
    // Constructor implementation

    // Create a new dungeon
    Dungeon dungeon = Dungeon();
    dungeons.push_back(dungeon);

    // Create a new room
    Room room = Room();
    rooms.push_back(room);
}