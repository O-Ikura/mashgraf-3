#include "Level.h"
#include <iostream>
#include <fstream>

Level::Level(const std::vector<std::string> &sprite_paths)
    : info(MAP_SIZE, std::vector<char>(MAP_SIZE))
    , lvl(MAP_SIZE, std::vector<char>(MAP_SIZE))
    , background(MAP_SIZE * tileSize, MAP_SIZE * tileSize, 4)
    , tile_sprites(NUM_OF_TILES)
{
    for (int i = 0; i < NUM_OF_TILES; ++i) {
        //std::cout << sprite_paths[i] << std::endl;
        Image *tmp = new Image(sprite_paths[i]);
        tile_sprites[i] = tmp;
    }
};

void Level::ReadFromFile(const std::string &a_path) {

    std::ifstream file(a_path);
    for (int x = 0; x < MAP_SIZE; ++x) {
        for (int y = 0; y < MAP_SIZE; ++y) {
            char tmp;
            file >> tmp;
            info[x][y] = tmp;
            switch (tmp)
            {
            case '@':
                start_pos.x = x * tileSize;
                start_pos.y = y * tileSize;
            case 'S':
            case 'T':
            case '.':
                lvl[x][y] = Tile::FLOOR;
                break;
            
            case '#':
                lvl[x][y] = Tile::WALL;
                break;
            
            case 'X':
                lvl[x][y] = Tile::FINISH;
                finish_pos.x = x * tileSize;
                finish_pos.y = y * tileSize;
                break;
            
            default:
                break;
            }
        }
    }
    file.close();
}

void Level::Draw() {
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            tile_sprites[lvl[x][MAP_SIZE - y - 1]]->Draw(x * tileSize, y * tileSize, background);
        }
    }
}