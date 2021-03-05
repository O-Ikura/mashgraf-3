#include "Player.h"

Player::Player(Point pos)
    : coords(pos)
    , old_coords(coords)
    , hit_points(100)
    , is_dead(false)
    , direction({false})
    , patient("../resources/player_patient.png")
    , dead("../resources/player_death_3.png")
    , run_right(true, std::vector<Image*>(
        {
            new Image("../resources/player_run_right_1.png"),
            new Image("../resources/player_run_right_2.png"),
            new Image("../resources/player_run_right_3.png"),
        }
    ))
    , run_left(true, std::vector<Image*>(
        {
            new Image("../resources/player_run_left_1.png"),
            new Image("../resources/player_run_left_2.png"),
            new Image("../resources/player_run_left_3.png"),
        }
    ))
    , deth_animation(false, std::vector<Image*>(
        {
            new Image("../resources/player_death_1.png"),
            new Image("../resources/player_death_2.png"),
            new Image("../resources/player_death_3.png"),
            //new Image("../resources/death_4.png"),
            //new Image("../resources/death_5.png")
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

void Player::Draw(Image &screen)
{
    if (is_dead && diying) {
        diying = !deth_animation.Draw(coords.x, coords.y, screen);
        return;
    }

    if (is_dead && !diying) {
        dead.Draw(coords.x, coords.y, screen);
        return;
    }
    
    if (!Moved())
    {
        patient.Draw(coords.x, coords.y, screen);
        old_coords = coords;
        return;
    } 

    if (direction[MovementDir::RIGHT]) {
        run_right.Draw(coords.x, coords.y, screen);
        direction[MovementDir::RIGHT] = false;
    }
    else if (direction[MovementDir::LEFT]) {
        run_left.Draw(coords.x, coords.y, screen);
        direction[MovementDir::LEFT] = false;
    }
    else if (direction[MovementDir::UP]) {
        run_left.Draw(coords.x, coords.y, screen);
        direction[MovementDir::UP] = false;
    }
    else if (direction[MovementDir::DOWN]) {
        run_right.Draw(coords.x, coords.y, screen);
        direction[MovementDir::DOWN] = false;
    }

    //tmp->Draw(coords.x, coords.y, screen);
}

Player::~Player() {}