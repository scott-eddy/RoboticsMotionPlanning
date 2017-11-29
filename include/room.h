
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

   virtual const SpaceRepresentation2D& GetRoomSpaceRepresentation(void){
   return space_matrix_;
  };

 protected:
  Room() = default;

  /**
   * Protected Ctor, allows derived classes to instanciate a space_matrix_ directly via passing in values to the protected
   * base class constructor
   */
  Room(size_t x_space, size_t y_space, SpaceRepresentation2D::SpaceType fill_type) : space_matrix_(x_space, y_space, fill_type) {};

  /**
   * The pose of the room with respect to the map.
   * The location of the pose is the room's center
   */
  map_tools::geometry::Pose2D pose_;
  SpaceRepresentation2D space_matrix_;
};

inline Room::~Room() {}