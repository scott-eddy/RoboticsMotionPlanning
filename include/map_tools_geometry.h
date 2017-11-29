
#pragma once

namespace map_tools::geometry {

/**
 * A point in 2 dimensional space
 */
struct Point2D{
  Point2D() : x(0), y(0) {};
  int x;
  int y;
};

/**
 * A rectangle in 2 dimensional space
 */
struct Rectangle {
  Rectangle(): top_left(), bottom_right(){};
  Point2D top_left;
  Point2D bottom_right;
};

/**
 * A position and orientation in space
 */
struct Pose2D {
  Pose2D(): location(), orientation(0.0) {};
  Point2D location;
  double orientation;

};

}