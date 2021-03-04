#include "Image.h"
#include <vector>

class Animation {
public:
    Animation(
            bool inf,
            int timer,
            const std::vector<Image*> &frames);

    int Width()    const { return width; }
    int Height()   const { return height; }

    Image* GetImage() {
        timer++;
        if (timer % 10 == 0) {
            frame++;
        }
        if (inf) {
            return frames[frame % num_of_frames];
        }
        return NULL;
    }

    ~Animation();

private:
    bool inf = true;
    unsigned int frame = 0;
    unsigned int timer = 0;
    int num_of_frames = 0;
    std::vector<Image*> frames;

    int width = -1;
    int height = -1;

};