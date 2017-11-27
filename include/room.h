
#pragma once
#include "map_tools_geometry.h"
#include <space_representation_2D.h>
/**
 * @brief Abstract class defining what makes up a Room in a map
 * @details Note that the origin of the room is the upper left hand corner
 */
class Room {
 public:
  virtual ~Room() = 0;
  virtual map_tools::geometry::Rectangle GetBoundingBox() = 0;

 protected:
  Room() = default;

  /**
   * Protected Ctor, allows derived classes to instanciate a space_matrix_ directly via passing in values to the protected
   * base class constructor
   */
  Room(size_t x_space, size_t y_space) : space_matrix_(x_space, y_space) {};
  virtual void PopulateMap() = 0;
  map_tools::geometry::Point2D origin_;
  SpaceRepresentation2D space_matrix_;
};

inline Room::~Room() {}