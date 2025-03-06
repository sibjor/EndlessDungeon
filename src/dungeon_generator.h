#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#define DUNGEON_WIDTH 100
#define DUNGEON_HEIGHT 100
#define CORRIDOR_WIDTH 3

#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <random>
#include <ctime>

const char WALL_EAST = 'WE';
const char WALL_WEST = 'WW';
const char WALL_NORTH = 'WN';
const char WALL_SOUTH = 'WS';
const char FLOOR = 'FL';
const char STAIR_UP = 'SU';
const char STAIR_DOWN = 'SD';

class DungeonGenerator
{
public:
    DungeonGenerator(int width, int height, int timesDivided);
    ~DungeonGenerator();
    int GenerateRandomValue(int width, int height, bool isVertical); // Returns a random integer

private:
    int width, height; // Width and Height of the dungeon and Rooms
};

class Room
    {
    public:
        Room();
        ~Room();

    private:
        bool isFirst; // If true then it should have stairs up
        bool isAny;   // If true then it should not have stairs
        bool isLast;  // If true then it should have stairs down
        bool IsFirstRoom(int width, int height); // First DungeonGenerator should have stairs up
        bool IsAnyRoom(int width, int height);   // Does not have stairs
        bool IsLastRoom(int width, int height);  // Last DungeonGenerator should have stairs down
    };

#endif