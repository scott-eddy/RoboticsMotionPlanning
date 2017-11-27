
#include "rectangle_room.h"
#include <random> //Needed to add clutter to a room
#include <iostream>
RectangleRoom::RectangleRoom(const map_tools::geometry::Rectangle& bounding_box) :
// TODO [issue #2] this room has it's own space representation which are in room corrdinate space, however it should also
// TODO "pose" that allows transformation back into map space
Room ((bounding_box.bottom_right_.x - bounding_box.top_left_.x), (bounding_box.bottom_right_.y-bounding_box.top_left_.y))
{
  bounding_box_ = bounding_box;
  origin_.x = (bounding_box_.bottom_right_.x - bounding_box_.top_left_.x) / 2;
  origin_.y = (bounding_box_.bottom_right_.y - bounding_box_.top_left_.y) / 2;
  PopulateMap();
}

void RectangleRoom::PopulateMap() {
  //Generate the remaining points to define the entire border of the map
  map_tools::geometry::Point2D upper_right_point;
  upper_right_point.x = bounding_box_.bottom_right_.x;
  upper_right_point.y = bounding_box_.top_left_.y;

  map_tools::geometry::Point2D lower_left_point;
  lower_left_point.x = bounding_box_.top_left_.x;
  lower_left_point.y = bounding_box_.bottom_right_.y;


  Line room_top_line(std::vector<map_tools::geometry::Point2D>({bounding_box_.top_left_, upper_right_point}));
  Line room_bottom_line(std::vector<map_tools::geometry::Point2D>({lower_left_point, bounding_box_.bottom_right_}));
  Line room_left_line(std::vector<map_tools::geometry::Point2D>({bounding_box_.top_left_, lower_left_point}));
  Line room_right_line(std::vector<map_tools::geometry::Point2D>({upper_right_point, bounding_box_.bottom_right_}));

  room_edges_in_map_frame_.push_back(room_top_line);
  room_edges_in_map_frame_.push_back(room_bottom_line);
  room_edges_in_map_frame_.push_back(room_left_line);
  room_edges_in_map_frame_.push_back(room_right_line);

}

map_tools::geometry::Rectangle RectangleRoom::GetBoundingBox() {
  return bounding_box_;
}

