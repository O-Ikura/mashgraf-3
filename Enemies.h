#include "Player.h"

class Enemy {
public:
    Enemy(Point pos);

    void Logic();
    void Draw();

    ~Enemy();

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
};