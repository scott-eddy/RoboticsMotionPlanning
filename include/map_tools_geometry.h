
#pragma once

namespace map_tools::geometry {


struct Point2D{
  int x;
  int y;
};

struct Rectangle {
  Point2D top_left_;
  Point2D bottom_right_;
};

}