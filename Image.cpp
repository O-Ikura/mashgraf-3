#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(const Image &orig)
    : width(orig.width)
    , height(orig.height)
    , channels(orig.channels)
    , size(orig.size)
    , data()
    , self_allocated(orig.self_allocated)
{
    if (orig.data) {
        data = new Pixel[size];
        for (int i = 0; i < size; ++i) {
            data[i] = orig.data[i];
        }
    }
}

Image::Image(const std::string &a_path)
{
    if ((data = (Pixel *)stbi_load(a_path.c_str(), &width, &height, &channels, 4)) != nullptr)
    {
        //channels = 4;
        size = width * height * channels;
    }
}

Image::Image(int a_width, int a_height, int a_channels)
{
    data = new Pixel[a_width * a_height]{};

    if (data != nullptr)
    {
        width = a_width;
        height = a_height;
        size = a_width * a_height * a_channels;
        channels = a_channels;
        self_allocated = true;
    }
}

int Image::Save(const std::string &a_path)
{
    auto extPos = a_path.find_last_of('.');
    if (a_path.substr(extPos, std::string::npos) == ".png" || a_path.substr(extPos, std::string::npos) == ".PNG")
    {
        stbi_write_png(a_path.c_str(), width, height, channels, data, width * channels);
    }
    else if (a_path.substr(extPos, std::string::npos) == ".jpg" || a_path.substr(extPos, std::string::npos) == ".JPG" ||
             a_path.substr(extPos, std::string::npos) == ".jpeg" || a_path.substr(extPos, std::string::npos) == ".JPEG")
    {
        stbi_write_jpg(a_path.c_str(), width, height, channels, data, 100);
    }
    else
    {
        std::cerr << "Unknown file extension: " << a_path.substr(extPos, std::string::npos) << "in file name" << a_path << "\n";
        return 1;
    }

    return 0;
}

void Image::Draw(int coord_x, int coord_y, Image &screen)
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            screen.PutPixel(
                    x + coord_x,
                    y + coord_y,
                    Blend(screen.GetPixel(x + coord_x, y + coord_y), GetPixel(x, height - y - 1))
            );
        }
    }
}

Pixel Image::Blend(Pixel oldPixel, Pixel newPixel)
{
    newPixel.r = newPixel.a / 255.0 * (newPixel.r - oldPixel.r) + oldPixel.r;
    newPixel.g = newPixel.a / 255.0 * (newPixel.g - oldPixel.g) + oldPixel.g;
    newPixel.b = newPixel.a / 255.0 * (newPixel.b - oldPixel.b) + oldPixel.b;
    newPixel.a = 255;

    return newPixel;
}

Image::~Image()
{
    if (self_allocated)
        delete[] data;
    else
    {
        stbi_image_free(data);
    }
}
