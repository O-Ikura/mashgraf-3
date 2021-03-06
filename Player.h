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
    Player(Point pos = {.x = 10, .y = 10});

    bool Moved();
    bool IsDead() const { return is_dead; }
    bool IsDiying() const { return diying; }
    int GetHP() const { return hit_points; }
    void ProcessInput(int dir, std::vector<std::vector<char>> &lvl);
    void Patient() { old_coords = coords; }
    void Draw(Image &screen);

    Point GetCoords() const {
        return {
                .x = coords.x + spriteSize / 2,
                .y = coords.y + spriteSize / 2,
        }; }

    void SetCoords(Point pos) {
        coords.x = pos.x;
        coords.y = pos.y;
        old_coords.x = pos.x;
        old_coords.y = pos.y;
    }

    void Hit(int x) {
        hit_points -= x;
        if (hit_points <= 0) {
            is_dead = true;
            diying = true;
            hit_points = 0;
        }
    }

    ~Player();

private:
    Point coords{.x = 10, .y = 10};
    Point old_coords{.x = 10, .y = 10};
    int hit_points = 100;
    int move_speed = 4;

    bool is_dead = false;
    bool diying = false;
    bool direction[4];

    Image patient;
    Image dead;
    Animation run_right;
    Animation run_left;
    Animation deth_animation;
    //std::vector<Animation*> running;
    //std::vector<Image*> attack;
};

/*
class GUI {
public:
    GUI();

private:
    Point hp_pos;
    std::vector<Image*> numbers;

};*/


#endif //MAIN_PLAYER_H
