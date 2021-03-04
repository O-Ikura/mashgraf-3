#include "Level.h"
#include <iostream>
#include <fstream>

Level::Level(
        const std::string &level_name,
        const std::vector<std::string> &sprite_paths)
    : path(level_name)
    , lvl(MAP_SIZE, std::vector<char>(MAP_SIZE))
    , background(MAP_SIZE * tileSize, MAP_SIZE * tileSize, 4)
    , tile_sprites(NUM_OF_TILES)
{
    std::ifstream file(level_name);

    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            char tmp;
            file >> tmp;
            switch (tmp)
            {
            case '@':
                start_pos.x = i;
                start_pos.y = j;
            case '.':
                lvl[i][j] = Tile::FLOOR;
                break;
            
            case '#':
                lvl[i][j] = Tile::WALL;
                break;
            
            case 'T':
                lvl[i][j] = Tile::TRAP;
                break;
            
            default:
                break;
            }
        }
    }
    file.close();

    for (int i = 0; i < NUM_OF_TILES; ++i) {
        //std::string tmp(sprite_paths[i]);
        std::cout << sprite_paths[i] << std::endl;
        Image *tmp = new Image(sprite_paths[i]);
        tile_sprites[i] = tmp;

    }

    //std::cout << tile_sprites[0]->Width() << " " << tile_sprites[0]->Height() << std::endl;
    //std::cout << tile_sprites[0]->Channels() << " " << tile_sprites[0]->Size() << std::endl;

    Draw();

};

void Level::Draw() {
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            tile_sprites[lvl[x][MAP_SIZE - y - 1]]->Draw(x * tileSize, y * tileSize, background);
        }
    }
}

/*
void Level::DrawTile(int x, int y, Image &tile, Image &background) {
    for(int y_draw = 0; y_draw < tileSize; ++y_draw) {
        for(int x_draw = 0; x_draw < tileSize; ++x_draw) {
            background.PutPixel(x * tileSize + x_draw, y * tileSize + y_draw, tile.GetPixel(x_draw, y_draw));
        }
    }
}
*/