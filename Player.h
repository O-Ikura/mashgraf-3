#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Animation.h"
#include "Level.h"

constexpr int spriteSize = 20;

enum MovementDir
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player
{
public:
    Player(Point pos);

    bool Moved();
    void ProcessInput(int dir, std::vector<std::vector<char>> &lvl);
    void Draw(Image &screen);

    ~Player();

private:
    Point coords{.x = 10, .y = 10};
    Point old_coords{.x = 10, .y = 10};
    Pixel color{.r = 255, .g = 255, .b = 0, .a = 255};
    int hit_points = 100;
    int move_speed = 4;

    bool direction[4];

    Image patient;
    Animation run_right;
    Animation run_left;
    //std::vector<Animation*> running;
    //std::vector<Image*> attack;
};

#endif //MAIN_PLAYER_H
