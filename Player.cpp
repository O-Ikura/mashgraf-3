#include "Player.h"

Player::Player(Point pos)
    : coords(pos)
    , old_coords(coords)
    , direction({false})
    , patient("../resources/player_patient.png")
    , running(std::vector<Image*>(4))
{
    running[MovementDir::UP] = new Image("../resources/player_run_right.png");
    running[MovementDir::RIGHT] = new Image("../resources/player_run_right.png");
    running[MovementDir::DOWN] = new Image("../resources/player_run_left.png");
    running[MovementDir::LEFT] = new Image("../resources/player_run_left.png");
}

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

void Player::ProcessInput(int dir)
{
    int move_dist = move_speed * 1;
    switch (dir)
    {
    case MovementDir::UP:
        old_coords.y = coords.y;
        coords.y += move_dist;
        break;
    case MovementDir::DOWN:
        old_coords.y = coords.y;
        coords.y -= move_dist;
        break;
    case MovementDir::LEFT:
        old_coords.x = coords.x;
        coords.x -= move_dist;
        break;
    case MovementDir::RIGHT:
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

    for (int y = 0; y < spriteSize; ++y)
    {
        for (int x = 0; x < spriteSize; ++x)
        {
            Image *tmp = &patient;
            if (direction[MovementDir::UP]) {
                tmp = running[MovementDir::UP];
            }
            if (direction[MovementDir::DOWN]) {
                tmp = running[MovementDir::DOWN];
            }
            if (direction[MovementDir::RIGHT]) {
                tmp = running[MovementDir::RIGHT];
            }
            if (direction[MovementDir::LEFT]) {
                tmp = running[MovementDir::LEFT];
            }

            screen.PutPixel(x + coords.x, y + coords.y, tmp->GetPixel(x, spriteSize - y));
        }
    }
}