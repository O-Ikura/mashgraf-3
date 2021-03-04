#include "Player.h"

Player::Player(Point pos)
    : coords(pos)
    , old_coords(coords)
    , hit_points(100)
    , direction({false})
    , patient("../resources/player_patient.png")
    , run_right(true, 0, std::vector<Image*>(
        {
            new Image("../resources/player_run_right_1.png"),
            new Image("../resources/player_run_right_2.png"),
            new Image("../resources/player_run_right_3.png"),
        }
    ))
    , run_left(true, 0, std::vector<Image*>(
        {
            new Image("../resources/player_run_left_1.png"),
            new Image("../resources/player_run_left_2.png"),
            new Image("../resources/player_run_left_3.png"),
        }
    ))
{}

bool Player::Moved()
{
    int delta_x = coords.x - old_coords.x;
    int delta_y = coords.y - old_coords.y;

    if (delta_x == 0 && delta_y == 0) {
        return false;
    }

    direction[MovementDir::UP] = (delta_y > 0);
    direction[MovementDir::RIGHT] = (delta_x > 0);
    direction[MovementDir::DOWN] = (delta_y < 0);
    direction[MovementDir::LEFT] = (delta_x < 0);
    return true;
}

void Player::ProcessInput(int dir, std::vector<std::vector<char>> &lvl)
{
    int move_dist = move_speed * 1;
    
    int x = (coords.x + spriteSize / 2) / tileSize ;
    int y = (coords.y + spriteSize / 2) / tileSize ;

    switch (dir)
    {
    case MovementDir::UP:
        if (lvl[x][y + 1] == Tile::WALL) {
            break;
        }
        old_coords.y = coords.y;
        coords.y += move_dist;
        break;
    case MovementDir::DOWN:
        if (lvl[x][y - 1] == Tile::WALL) {
            break;
        }
        old_coords.y = coords.y;
        coords.y -= move_dist;
        break;
    case MovementDir::LEFT:
        if (lvl[x - 1][y] == Tile::WALL) {
            break;
        }
        old_coords.x = coords.x;
        coords.x -= move_dist;
        break;
    case MovementDir::RIGHT:
        if (lvl[x + 1][y] == Tile::WALL) {
            break;
        }
        old_coords.x = coords.x;
        coords.x += move_dist;
        break;
    default:
        break;
    }
}

void Player::Draw(Image &screen, Image &background)
{
    if (Moved())
    {
        for (int y = old_coords.y; y <= old_coords.y + spriteSize; ++y)
        {
            for (int x = old_coords.x; x <= old_coords.x + spriteSize; ++x)
            {
                screen.PutPixel(x, y, background.GetPixel(x, y));
            }
        }
        old_coords = coords;
    }

    Image *tmp = &patient;
    if (direction[MovementDir::UP]) {
        tmp = run_left.GetImage();
        direction[MovementDir::UP] = false;
    }
    if (direction[MovementDir::DOWN]) {
        tmp = run_right.GetImage();
        direction[MovementDir::DOWN] = false;
    }
    if (direction[MovementDir::RIGHT]) {
        tmp = run_right.GetImage();
        direction[MovementDir::RIGHT] = false;
    }
    if (direction[MovementDir::LEFT]) {
        tmp = run_left.GetImage();
        direction[MovementDir::LEFT] = false;
    }

    for (int y = 0; y < spriteSize; ++y) {
        for (int x = 0; x < spriteSize; ++x) {
            screen.PutPixel(
                    x + coords.x,
                    y + coords.y,
                    blend(background.GetPixel(x + coords.x, y + coords.y), tmp->GetPixel(x, spriteSize - y - 1))
            );
        }
    }
}

Player::~Player() {}