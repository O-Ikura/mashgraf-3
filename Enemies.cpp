#include "Enemies.h"

Image* Enemy::PushSprite(const std::string &a_path) {
    Image *tmp = new Image(a_path);
    sprites.push_back(tmp);
    return tmp;
}

Trap::Trap(Point pos)
    : coords(pos)
    , inactive(PushSprite("../resources/trap_inactive.png"))
    , active(PushSprite("../resources/trap_active.png"))
{}

void Trap::Update(Player &player) {
    Point tmp = player.GetCoords();
    if (
            (coords.x <= tmp.x) &&
            (tmp.x <= coords.x + inactive->Width()) &&
            (coords.y <= tmp.y) &&
            (tmp.y <= coords.y + inactive->Height())
        )
    {
        is_active = true;
        player.Hit(25);
    }
}

void Trap::Draw(Image &screen) {
    if (is_active) {
        active->Draw(coords.x, coords.y, screen);
    }
    else {
        inactive->Draw(coords.x, coords.y, screen);
    }
}