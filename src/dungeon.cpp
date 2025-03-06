#include "dungeon.h"
#include "random.h"

Dungeon::Dungeon()
{
    // Constructor

    // Add metadata to save file (not implemented)
}

Room::Room()
{
    // Constructor

    for (int i = 0; i < random(5, 10); i++)
    {
        for (int j = 0; j < random(5, 10); j++)
        {
            Tile tile = Tile();
            // Implement logic to set compass based on adjacent tiles
            if (tile.hasAdjacentBlank){
                
            }
            tile.posX = i;
            tile.posY = j;
            tiles[i][j] = tile;
        }
    }
}