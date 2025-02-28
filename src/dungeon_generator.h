#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#include <vector>
#include <SDL3/SDL.h>

const int WIDTH = 80;  // Width of the dungeon
const int HEIGHT = 45; // Height of the dungeon
const char WALL = '#';
const char FLOOR = '.';
const char START = 'S';
const char END = 'E';

struct Room {
    int x, y, width, height;
};

std::vector<std::vector<char>> generateDungeon();
void printDungeon(const std::vector<std::vector<char>>& dungeon);
SDL_Texture* getWallTexture(int x, int y, const std::vector<std::vector<char>>& dungeon);
void renderDungeon(SDL_Renderer* renderer, const std::vector<std::vector<char>>& dungeon);

#endif