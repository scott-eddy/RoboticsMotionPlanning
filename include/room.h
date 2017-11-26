
#pragma once
#include "map_tools_geometry.h"
/**
 * @brief Abstract class defining what makes up a Room in a map
 * @details Note that the origin of the room is the upper left hand corner
 */
class Room {
 public:
  virtual ~Room() = 0;
  virtual map_tools::geometry::Rectangle GetBoundingBox() = 0;
  //virtual void addWall(const Wall& wallToAdd) = 0;
  virtual void AddClutter() = 0;

 protected:
  Room() = default;
  virtual void PopulateMap() = 0;
  int x_free_space_;
  int y_free_space_;
  map_tools::geometry::Point2D origin;
};

inline Room::~Room() {}