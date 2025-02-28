#include "dungeon_generator.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

std::vector<std::vector<char>> generateDungeon() {
    std::vector<std::vector<char>> dungeon(HEIGHT, std::vector<char>(WIDTH, WALL));
    std::vector<Room> rooms;
    srand(time(0));

    // Generate rooms
    for (int i = 0; i < 10; ++i) {
        int roomWidth = rand() % 6 + 5;
        int roomHeight = rand() % 6 + 5;
        int x = rand() % (WIDTH - roomWidth - 1) + 1;
        int y = rand() % (HEIGHT - roomHeight - 1) + 1;

        Room room = {x, y, roomWidth, roomHeight};
        rooms.push_back(room);

        for (int r = y; r < y + roomHeight; ++r) {
            for (int c = x; c < x + roomWidth; ++c) {
                dungeon[r][c] = FLOOR;
            }
        }
    }

    // Connect rooms with corridors
    for (size_t i = 1; i < rooms.size(); ++i) {
        int x1 = rooms[i - 1].x + rooms[i - 1].width / 2;
        int y1 = rooms[i - 1].y + rooms[i - 1].height / 2;
        int x2 = rooms[i].x + rooms[i].width / 2;
        int y2 = rooms[i].y + rooms[i].height / 2;

        while (x1 != x2) {
            dungeon[y1][x1] = FLOOR;
            x1 += (x2 > x1) ? 1 : -1;
        }
        while (y1 != y2) {
            dungeon[y1][x1] = FLOOR;
            y1 += (y2 > y1) ? 1 : -1;
        }
    }

    // Set start and end points
    dungeon[rooms[0].y + rooms[0].height / 2][rooms[0].x + rooms[0].width / 2] = START;
    dungeon[rooms.back().y + rooms.back().height / 2][rooms.back().x + rooms.back().width / 2] = END;

    return dungeon;
}

void printDungeon(const std::vector<std::vector<char>>& dungeon) {
    for (const auto& row : dungeon) {
        for (char tile : row) {
            std::cout << tile;
        }
        std::cout << std::endl;
    }
}