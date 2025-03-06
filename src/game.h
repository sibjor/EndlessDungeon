#include "dungeon.h"

class Game{
    public:
        Game();
        ~Game();
        
    private:
        std::vector<Dungeon> dungeons;

};

struct SaveData{
    static std::vector<int> saveFiles;
};