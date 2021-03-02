#include <vector>
#include "Player.h"

enum {
    MAP_SIZE = 40,
    NUM_OF_TILES = 3,
};

enum Tile {
    WALL,
    FLOOR,
    TRAP,
    PLAYER,
};

struct Level {

    explicit Level(
            const std::string &level_name,
            const std::vector<std::string> &sprite_paths);

    //void ReadFromFile();
    void Draw(Image &screen);
    void DrawTile(int x, int y, Image &tile, Image &background);
    //void DrawTile(const Image &tile) const;

private:
    std::string path;
    std::vector<std::vector<char>> lvl;
    std::vector<Image*> tile_sprites;
    Point start_pos;

};