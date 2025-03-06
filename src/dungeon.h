#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#define EAST = "EAST";
#define WEST = "WEST";
#define NORTH = "NORTH";
#define SOUTH = "SOUTH";
#define NORTHEAST = "NORTHEAST";
#define SOUTHEAST = "SOUTHEAST";
#define NORTHWEST = "NORTHWEST";
#define SOUTHWEST = "SOUTHWEST";


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

struct Tile
{
    char type;
    int posX;
    int posY;

};

class FirstFloor : public Dungeon
{
public:
    FirstFloor();
    ~FirstFloor();

private:
    int roomCount;
    std::vector<Room> rooms;
};

class Dungeon
{
public:
    Dungeon();
    ~Dungeon();

private:
    int roomCount;
    std::vector<Room> rooms;
};

class Room
{
public:
    Room();
    ~Room();

private:

    Tile tiles[10][10];
};

#endif