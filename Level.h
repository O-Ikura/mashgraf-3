#include <vector>
//#include "Player.h"
#include "Image.h"

enum Tile {
    WALL,
    FLOOR,
    FINISH,
    TRAP,
    PLAYER,
    SLIME,
};

class Level {
public:

    explicit Level(const std::vector<std::string> &sprite_paths);

    void ReadFromFile(const std::string &a_path);
    void Draw();

    Point GetStartPos() { return start_pos; }
    Point GetFinishPos() { return finish_pos; }

    Image& GetImage() { return background; }
    std::vector<std::vector<char>>& GetInfo() { return info; }
    std::vector<std::vector<char>>& GetMap() { return lvl; }

private:
    std::vector<std::vector<char>> info;
    std::vector<std::vector<char>> lvl;

    Image background;
    std::vector<Image*> tile_sprites;
    Point start_pos;
    Point finish_pos;

};