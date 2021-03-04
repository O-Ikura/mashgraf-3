#include "Animation.h"

Animation::Animation(
            bool inf,
            int timer,
            const std::vector<Image*> &frames)
    : inf(inf)
    , frame(0)
    , timer(timer)
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
    //std::cout << frame << std::endl;

    if (curr_check - last_check > 0.5) {
        frame++;
        last_check = curr_check;
    }

    if (frame == num_of_frames) {
        frame = 0;
        if (!inf) {
            return true;
        }
    }
    return false;

}

Animation::~Animation() {
    for (auto i: frames) {
        delete i;
    }
}