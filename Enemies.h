#include "Player.h"

class Enemy {
public:
    Enemy(): sprites() {}

    virtual bool Moved() = 0;
    virtual void Update(Player &player, std::vector<std::vector<char>> &lvl) = 0;
    virtual void Draw(Image &screen) = 0;
    virtual Point GetCoords() const = 0;
    virtual void Hit(int x) = 0;

    Image* PushSprite(const std::string &a_path);
    //Animation* PushAnimation(bool inf, const std::vector<Image*> &frames);

    ~Enemy() {}

private:
    Point coords;
    int hit_points;
    bool is_dead = false;
    std::vector<Image*> sprites;
    //std::vector<Animation*> animations;
};

class Trap : virtual public Enemy {
public:
    Trap(Point pos);

    bool Moved() { return false; }
    void Update(Player &player, std::vector<std::vector<char>> &lvl);
    void Draw(Image &screen);

    Point GetCoords() const {
    return {
            .x = coords.x + tileSize / 2,
            .y = coords.y + tileSize / 2,
    }; }

    void Hit(int x) {}

private:
    static bool allocated;
    int hit_points = 99999999;
    bool is_active = false;
    bool is_dead = false;
    GLfloat last_check;
    Point coords;
    Image *inactive;
    Image *active;

};

class Slime : virtual public Enemy {
public:
    Slime(Point pos);

    bool Moved();
    void Update(Player &player, std::vector<std::vector<char>> &lvl);
    void Draw(Image &screen);
    
    Point GetCoords() const {
    return {
        .x = coords.x + tileSize / 2,
        .y = coords.y + tileSize / 2,
    }; }

    void Hit(int x) {
        hit_points -= x;
        if (hit_points <= 0) {
            is_dead = true;
        }
    }

private:
    int move_speed = 1;
    int hit_points = 100;
    bool is_dead = false;
    bool direction[4];
    GLfloat last_check;

    Point coords;
    Image *patient;
    Image *corpse;
    Animation *run_left;
    Animation *run_right;
};