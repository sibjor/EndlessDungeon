#include "dungeon_generator.h"
#include "texture_loader.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

const int MIN_ROOM_SIZE = 5; // Define the minimum room size

struct Node {
    int x, y, width, height;
    Node* left;
    Node* right;
    Room room;

    Node(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), left(nullptr), right(nullptr) {}
};

bool splitNode(Node* node) {
    // Determine if we should split horizontally or vertically
    bool splitHorizontally = rand() % 2 == 0;

    // Ensure the split direction is valid
    if (node->width > node->height && node->width / node->height >= 1.25) {
        splitHorizontally = false;
    } else if (node->height > node->width && node->height / node->width >= 1.25) {
        splitHorizontally = true;
    }

    // Determine the maximum size of the split
    int max = (splitHorizontally ? node->height : node->width) - MIN_ROOM_SIZE;
    if (max <= MIN_ROOM_SIZE) {
        return false; // The node is too small to split
    }

    // Determine the split point
    int split = rand() % (max - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;

    // Create the left and right children
    if (splitHorizontally) {
        node->left = new Node(node->x, node->y, node->width, split);
        node->right = new Node(node->x, node->y + split, node->width, node->height - split);
    } else {
        node->left = new Node(node->x, node->y, split, node->height);
        node->right = new Node(node->x + split, node->y, node->width - split, node->height);
    }

    return true;
}

void createRooms(Node* node, std::vector<Room>& rooms) {
    if (node->left || node->right) {
        // This node has children, so recurse
        if (node->left) createRooms(node->left, rooms);
        if (node->right) createRooms(node->right, rooms);
    } else {
        // This node is a leaf, so create a room
        if (node->width > MIN_ROOM_SIZE && node->height > MIN_ROOM_SIZE) {
            int roomWidth = rand() % (node->width - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;
            int roomHeight = rand() % (node->height - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;
            int x = node->x + rand() % (node->width - roomWidth);
            int y = node->y + rand() % (node->height - roomHeight);

            node->room = {x, y, roomWidth, roomHeight};
            rooms.push_back(node->room);
        } else {
            // If the node is too small to create a room, create a minimal room
            node->room = {node->x, node->y, node->width, node->height};
            rooms.push_back(node->room);
        }
    }
}

void connectRooms(Node* node, std::vector<std::vector<char>>& dungeon) {
    if (node->left && node->right) {
        // Connect the rooms in the left and right children
        Room leftRoom = node->left->room;
        Room rightRoom = node->right->room;

        int x1 = leftRoom.x + leftRoom.width / 2;
        int y1 = leftRoom.y + leftRoom.height / 2;
        int x2 = rightRoom.x + rightRoom.width / 2;
        int y2 = rightRoom.y + rightRoom.height / 2;

        // Ensure x1, y1, x2, y2 are within bounds
        x1 = std::max(0, std::min(x1, WIDTH - 1));
        y1 = std::max(0, std::min(y1, HEIGHT - 1));
        x2 = std::max(0, std::min(x2, WIDTH - 1));
        y2 = std::max(0, std::min(y2, HEIGHT - 1));

        while (x1 != x2) {
            dungeon[y1][x1] = FLOOR;
            x1 += (x2 > x1) ? 1 : -1;
        }
        while (y1 != y2) {
            dungeon[y1][x1] = FLOOR;
            y1 += (y2 > y1) ? 1 : -1;
        }

        // Recurse to connect the rooms in the children
        connectRooms(node->left, dungeon);
        connectRooms(node->right, dungeon);
    }
}

void generateWalls(std::vector<std::vector<char>>& dungeon) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (dungeon[y][x] == FLOOR) {
                if (y > 0 && dungeon[y - 1][x] == ' ') dungeon[y - 1][x] = WALL;
                if (y < HEIGHT - 1 && dungeon[y + 1][x] == ' ') dungeon[y + 1][x] = WALL;
                if (x > 0 && dungeon[y][x - 1] == ' ') dungeon[y][x - 1] = WALL;
                if (x < WIDTH - 1 && dungeon[y][x + 1] == ' ') dungeon[y][x + 1] = WALL;
            }
        }
    }
}

std::vector<std::vector<char>> generateDungeon() {
    std::vector<std::vector<char>> dungeon(HEIGHT, std::vector<char>(WIDTH, ' '));
    std::vector<Room> rooms;
    srand(time(0));

    // Create the root node
    Node* root = new Node(0, 0, WIDTH, HEIGHT);

    // Split the root node until we can't split anymore
    std::vector<Node*> nodes = {root};
    while (!nodes.empty()) {
        Node* node = nodes.back();
        nodes.pop_back();

        if (splitNode(node)) {
            nodes.push_back(node->left);
            nodes.push_back(node->right);
        }
    }

    // Create rooms in the leaf nodes
    createRooms(root, rooms);

    // Connect the rooms with corridors
    connectRooms(root, dungeon);

    // Set start and end points
    if (!rooms.empty()) {
        dungeon[rooms[0].y + rooms[0].height / 2][rooms[0].x + rooms[0].width / 2] = START;
        dungeon[rooms.back().y + rooms.back().height / 2][rooms.back().x + rooms.back().width / 2] = END;
    }

    // Generate walls around the floors
    generateWalls(dungeon);

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