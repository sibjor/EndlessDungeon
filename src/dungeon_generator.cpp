#include "dungeon_generator2.h"

Room::Room(int w, int h, bool leaf, bool stairDown, bool stairUp){
    width = w;
    height = h;
    isLeaf = leaf;
    hasStairDown = stairDown;
    hasStairUp = stairUp;

    if (hasStairUp){
        isLeaf == false;
        hasStairDown == false;
        FirstRoom();
    }
}

void Room::FirstRoom() {
    // Implementation of FirstRoom
    CreateRoomWithStair();
}

Room::~Room() {
    // Destructor implementation
}

