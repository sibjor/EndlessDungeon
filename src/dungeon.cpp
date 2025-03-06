#include "dungeon.h"
#include "random.h"

struct Tile
{
    char type;
    int posX;
    int posY;
};

FirstFloor::FirstFloor(){
    // Constructor
    roomCount = random(5, 10);
    for (int i = 0; i < roomCount; i++)
    {
        Room room = Room();
        rooms.push_back(room);
    }
}

Dungeon::Dungeon(){
    // Constructor
    roomCount = random(5, 10);
    for (int i = 0; i < roomCount; i++)
    {
        Room room = Room();
        rooms.push_back(room);
    }
}

Room::Room(){
    // Constructor
    int value = random(5,10);
    for (int i = 0; i < value; i++)
    {
        for (int j = 0; j < value; j++)
        {
            Tile tile = Tile();
            tile.posX = i;
            tile.posY = j;
            tiles[i][j] = tile;
        }
    }
}