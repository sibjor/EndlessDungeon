#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <random>
#include <ctime>

const int WIDTH = 100;
const int HEIGHT = 100;
const int CORRIDOR_WIDTH = 3;
const char WALL_EAST = 'WE';
const char WALL_WEST = 'WW';
const char WALL_NORTH = 'WN';
const char WALL_SOUTH = 'WS';
const char FLOOR = 'FL';
const char STAIR_UP = 'SU';
const char STAIR_DOWN = 'SD';

class Dungeon
{
public:
    Dungeon();
    ~Dungeon();
    int GenerateRandom(int width, int height, bool isVertical); // Method to generate random numbers as well as the direction of the split
    void CalculateBSPArea(int width, int height); // Method to calculate BSP area

private:
    int width, height; // Width and Height of the dungeon and Rooms
    class Room
    {
    public:
        Room();
        ~Room();
        void CalculateRooms(); 

    private:
        bool isFirst; // If true then it should have stairs up
        bool isAny;   // If true then it should not have stairs
        bool isLast;  // If true then it should have stairs down
        bool IsFirstRoom(int width, int height); // First Dungeon should have stairs up
        bool IsAnyRoom(int width, int height);   // Does not have stairs
        bool IsLastRoom(int width, int height);  // Last Dungeon should have stairs down
    };
};

#endif