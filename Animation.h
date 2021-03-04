#include "Image.h"
#include <vector>
#include <GLFW/glfw3.h>

class Animation {
public:
    Animation(
            bool inf,
            int timer,
            const std::vector<Image*> &frames);

    int Width()    const { return width; }
    int Height()   const { return height; }

    bool Draw(int coord_x, int coord_y, Image &screen);

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
    unsigned int frame = -1;
    unsigned int timer = 0;
    int num_of_frames = 0;
    std::vector<Image*> frames;

    GLfloat last_check;

    int width = -1;
    int height = -1;

};