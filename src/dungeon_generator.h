#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#include <vector>

const int WIDTH = 50;
const int HEIGHT = 50;
const char EMPTY = ' ';
const char WALL = '#';
const char FLOOR = '.';
const char START = 'S';
const char END = 'E';

struct Room {
    int x, y, width, height;
};

std::vector<std::vector<char>> generateDungeon();
void printDungeon(const std::vector<std::vector<char>>& dungeon);

#endif 