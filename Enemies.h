#include "Player.h"

class Enemy {
public:
    Enemy(): sprites() {}

    virtual bool Moved() = 0;
    virtual void Update(Player &player) = 0;
    virtual void Draw(Image &screen) = 0;

    Image* PushSprite(const std::string &a_path);

    ~Enemy() {}

private:
    std::vector<Image*> sprites;
};

class Trap : virtual public Enemy {
public:
    Trap(Point pos);

    bool Moved() { return false; }
    void Update(Player &player);
    void Draw(Image &screen);

private:
    bool is_active = false;
    Point coords;
    Image *inactive;
    Image *active;

};