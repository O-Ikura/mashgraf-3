#include "Animation.h"

Animation::Animation(
            bool inf,
            const std::vector<Image*> &frames)
    : inf(inf)
    , frame(0)
    , frames(frames)
    , num_of_frames(frames.size())
    , last_check(glfwGetTime())
    , width(frames[0]->Width())
    , height(frames[0]->Height())
{
    std::cout << num_of_frames << std::endl;
}

bool Animation::Draw(int coord_x, int coord_y, Image &screen) {
    GLfloat curr_check = glfwGetTime();
    frames[frame]->Draw(coord_x, coord_y, screen);

    if (curr_check - last_check > 0.5) {
        frame++;
        last_check = curr_check;
    }

    if (frame == num_of_frames) {
        if (!inf) {
            return true;
        }
        frame = 0;
    }
    return false;

}

Animation::~Animation() {
    for (auto i: frames) {
        delete i;
    }
}