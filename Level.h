#include <vector>
//#include "Player.h"
#include "Image.h"

enum Tile {
    WALL,
    FLOOR,
    TRAP,
    PLAYER,
};

class Level {
public:

    explicit Level(
            const std::string &level_name,
            const std::vector<std::string> &sprite_paths);

    //void ReadFromFile();
    void Draw();

    Image& GetImage() { return background; }
    std::vector<std::vector<char>>& GetInfo() { return info; }
    std::vector<std::vector<char>>& GetMap() { return lvl; }

private:
    std::string path;
    std::vector<std::vector<char>> info;
    std::vector<std::vector<char>> lvl;

    Image background;
    std::vector<Image*> tile_sprites;
    Point start_pos;

};