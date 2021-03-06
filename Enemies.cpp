#include "Enemies.h"

Image* Enemy::PushSprite(const std::string &a_path) {
    sprites.push_back(new Image(a_path));
    return sprites.back();
}

Trap::Trap(Point pos)
    : coords(pos)
    , last_check(glfwGetTime())
    , inactive(PushSprite("../resources/trap_inactive.png"))
    , active(PushSprite("../resources/trap_active.png"))
{}

void Trap::Update(Player &player, std::vector<std::vector<char>> &lvl) {
    Point tmp = player.GetCoords();
    if (
            (coords.x <= tmp.x) &&
            (tmp.x <= coords.x + inactive->Width()) &&
            (coords.y <= tmp.y) &&
            (tmp.y <= coords.y + inactive->Height())
        )
    {
        is_active = true;
        GLfloat curr_check = glfwGetTime();
        if (curr_check - last_check > 1.0) {
            last_check = curr_check;
            player.Hit(25);
        }
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

Slime::Slime(Point pos)
    : coords(pos)
    , direction({false})
    , last_check(glfwGetTime())
    , patient(PushSprite("../resources/slime_patient.png"))
    , corpse(PushSprite("../resources/slime_dead.png"))
    , run_left(new Animation(true, std::vector<Image*>({
        new Image("../resources/slime_run_left_1.png"),
        new Image("../resources/slime_run_left_2.png"),
    })))
    , run_right(new Animation(true, std::vector<Image*>({
        new Image("../resources/slime_run_right_1.png"),
        new Image("../resources/slime_run_right_2.png"),
    })))
{}

void Slime::Update(Player &player, std::vector<std::vector<char>> &lvl) {
    if (is_dead) {
        return;
    }

    int delta_x = player.GetCoords().x - coords.x + patient->Width() /2;
    int delta_y = player.GetCoords().y - coords.y + patient->Height() /2;
    for (int i = 0; i < 4; ++i) {
        direction[i] = false;
    }
    if (abs(delta_x) <= 8 * tileSize && abs(delta_y) <= 8 * tileSize) {

        if (abs(delta_x) <= tileSize && abs(delta_y) <= tileSize) {
            GLfloat curr_check = glfwGetTime();
            if (curr_check - last_check > 1.0) {
                last_check = curr_check;
                player.Hit(10);
            }
        } else {

            int x = (coords.x + patient->Width() /2 / 2) / tileSize ;
            int y = (coords.y + patient->Height() / 2) / tileSize ;

            if (delta_x > 0 && !(lvl[x + 1][y] == Tile::WALL)) {
                direction[RIGHT] = true;
                coords.x += move_speed;
            } else if (delta_x < 0 && !(lvl[x - 1][y] == Tile::WALL)) {
                direction[LEFT] = true;
                coords.x -=move_speed;
            }
            if (delta_y > 0 && !(lvl[x][y + 1] == Tile::WALL)) {
                direction[UP] = true;
                coords.y += move_speed;
            } else if (delta_y < 0 && !(lvl[x][y - 1] == Tile::WALL)) {
                direction[DOWN] = true;
                coords.y -= move_speed;
            }

        }

    }
}

bool Slime::Moved() {
    for (auto i: direction) {
        if (i) {
            return i;
        }
    }
    return false;
}

void Slime::Draw(Image &screen) {
    if (is_dead) {
        corpse->Draw(coords.x, coords.y, screen);
        return;
    }

    if (!Moved()) {
        //std::cout << "слаймстоит\n";
        patient->Draw(coords.x, coords.y, screen);
    } else {
        if (direction[UP] || direction[LEFT]) {
            run_left->Draw(coords.x, coords.y, screen);
        }
        if (direction[DOWN] || direction[RIGHT]) {
            run_right->Draw(coords.x, coords.y, screen);
        }
    }
}