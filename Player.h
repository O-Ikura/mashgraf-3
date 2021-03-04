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
    bool IsDead() { return is_dead; }
    void ProcessInput(int dir, std::vector<std::vector<char>> &lvl);
    void Patient() { old_coords = coords; }
    void Draw(Image &screen);

    Point GetCoords() {
        return {
                .x = coords.x + spriteSize / 2,
                .y = coords.y + spriteSize / 2,
        }; }

    void Hit(int x) {
        hit_points -= x;
        //::cout << hit_points << std::endl;
        if (hit_points <= 0) {
            is_dead = true;
            hit_points = 0;
            //std::cout << "ya ded" << std::endl;
            //do something
        }
    }

    ~Player();

private:
    Point coords{.x = 10, .y = 10};
    Point old_coords{.x = 10, .y = 10};
    int hit_points = 100;
    int move_speed = 4;

    bool is_dead = false;
    bool direction[4];

    Image patient;
    Animation run_right;
    Animation run_left;
    Animation deth_animation;
    //std::vector<Animation*> running;
    //std::vector<Image*> attack;
};

#endif //MAIN_PLAYER_H
