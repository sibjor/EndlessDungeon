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

class FirstFloor : public Dungeon
{
public:
    FirstFloor();
    ~FirstFloor();
};

class Dungeon
{
public:
    Dungeon();
    ~Dungeon();

private:
    int width;
    int height;
    std::vector<Room> rooms;
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

        int width;
        int height;
        int posX; // Position X
        int posY; // Position Y
    };

#endif