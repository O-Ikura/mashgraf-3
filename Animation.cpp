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
    , width(frames[0]->Width())
    , height(frames[0]->Height())
{
    std::cout << num_of_frames << std::endl;
}

Animation::~Animation() {
    for (auto i: frames) {
        delete i;
    }
}