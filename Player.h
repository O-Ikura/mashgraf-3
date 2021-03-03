#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"
#include <vector>

constexpr int spriteSize = 20;

struct Point
{
  int x;
  int y;
};

enum MovementDir
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct Player
{
  explicit Player(Point pos = {.x = 10, .y = 10});

  bool Moved();
  void ProcessInput(int dir);
  void Draw(Image &screen, Image &background);

private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};
  int move_speed = 4;

  bool direction[4];

  Image patient;
  std::vector<Image*> running;
  //std::vector<Image*> attack;

};

#endif //MAIN_PLAYER_H
