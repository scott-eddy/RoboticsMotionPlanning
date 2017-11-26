#pragma once
#include "room.h"
#include <cmath>
#include "line.h"

/**
 * \brief A class representing a room that is in the shape of a triangle
 */
class RectangleRoom : public Room {
 public:
  RectangleRoom(int xFreeSpace, int yFreeSpace, const map_tools::geometry::Point2D &origin);

  ~RectangleRoom() = default;

  map_tools::geometry::Rectangle GetBoundingBox() override;

  void AddClutter() override;

 private:
  void PopulateMap() override;
  map_tools::geometry::Point2D upper_left_;
  map_tools::geometry::Point2D lower_right_;

};