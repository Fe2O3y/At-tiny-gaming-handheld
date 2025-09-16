

#ifndef BALL_H
#define BALL_H

#include <Adafruit_SSD1306.h>
#include <math.h>

class Ball{
  public:
  Ball(int x, int y, int box_height, int box_width);
  void iterate(Adafruit_SSD1306 dis);
  void set_position(int x, int y);
  int x_pos, y_pos;

  private:
  float heading[2];
  float new_x, new_y;
  bool check_collision(Adafruit_SSD1306 dis);
  void calc_new_heading(Adafruit_SSD1306 dis);
};

#endif