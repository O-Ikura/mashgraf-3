#ifndef MAIN_IMAGE_H
#define MAIN_IMAGE_H

#include <string>
#include <iostream>

constexpr int MAP_SIZE = 40;
constexpr int NUM_OF_TILES = 4;

struct Point
{
    int x;
    int y;
};

constexpr int tileSize = 16;

struct Pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

constexpr Pixel backgroundColor{0, 0, 0, 0};

class Image {
public:
    explicit Image(const Image &orig);
    explicit Image(const std::string &a_path);
    Image(int a_width = 16, int a_height = 16, int a_channels = 4);

    int Save(const std::string &a_path);
    void Draw(int coord_x, int coord_y, Image &screen);
    Pixel Blend(Pixel oldPixel, Pixel newPixel);

    int Width() const { return width; }
    int Height() const { return height; }
    int Channels() const { return channels; }
    size_t Size() const { return size; }
    Pixel *Data() { return data; }

    Pixel GetPixel(int x, int y) { return data[width * y + x]; }
    void PutPixel(int x, int y, const Pixel &pix) { data[width * y + x] = pix; }

    ~Image();

private:
    int width = -1;
    int height = -1;
    int channels = 4;
    size_t size = 0;
    Pixel *data = nullptr;
    bool self_allocated = false;
};

#endif //MAIN_IMAGE_H