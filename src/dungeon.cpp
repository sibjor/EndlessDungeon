#include "dungeon.h"
#include "random.h"


Dungeon::Dungeon(int timesDivided) {
    // Constructor implementation
    width = DUNGEON_WIDTH;
    height = DUNGEON_HEIGHT;
    this->timesDivided = timesDivided;
    
}

Dungeon::~Dungeon() {
    // Destructor implementation
}
Room::~Room() {
    // Destructor implementation
}

