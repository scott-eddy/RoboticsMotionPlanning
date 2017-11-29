#pragma once
#include "room.h"
#include <cmath>
#include "line.h"

/**
 * \brief A class representing a room that is in the shape of a triangle
 */
class RectangleRoom : public Room {
 public:
  RectangleRoom(const map_tools::geometry::Rectangle &bounding_box,
                  const double orientation);

  ~RectangleRoom() = default;

 private:
  map_tools::geometry::Rectangle bounding_box_;
};