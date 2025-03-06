#include "dungeon.h"

class Game{
    public:
        Game();
        ~Game();
        
    private:
        std::vector<Dungeon> dungeons;
        std::vector<Room> rooms;
};