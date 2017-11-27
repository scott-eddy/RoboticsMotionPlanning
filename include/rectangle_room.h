#pragma once
#include "room.h"
#include <cmath>
#include "line.h"

/**
 * \brief A class representing a room that is in the shape of a triangle
 */
class RectangleRoom : public Room {
 public:
  RectangleRoom(const map_tools::geometry::Rectangle& bounding_box);

  ~RectangleRoom() = default;

  map_tools::geometry::Rectangle GetBoundingBox() override;

  // TODO [issue #2] likely owning map should calculate and hold this info
  const std::vector<Line>& GetRoomEdgesInMapFrame(){
    return room_edges_in_map_frame_;
  }

 private:
  void GenerateRoomEdges() override;
  map_tools::geometry::Rectangle bounding_box_;

  // TODO [issue #2] likely owning map should calculate and hold this info
  std::vector<Line> room_edges_in_map_frame_;

};