
#pragma once

namespace map_tools::geometry {


struct Point2D{
  Point2D() : x(0), y(0) {};
  int x;
  int y;
};

struct Rectangle {
  Rectangle(): top_left_(), bottom_right_(){};
  Point2D top_left_;
  Point2D bottom_right_;
};

}