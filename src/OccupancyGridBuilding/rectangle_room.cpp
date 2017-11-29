
#include "rectangle_room.h"
#include <random> //Needed to add clutter to a room
#include <iostream>
RectangleRoom::RectangleRoom(const map_tools::geometry::Rectangle &bounding_box,
                             const double orientation) :
// TODO [issue #2] this room has it's own space representation which are in room corrdinate space, however it should also
// TODO "pose" that allows transformation back into map space
Room ((bounding_box.bottom_right.x - bounding_box.top_left.x), (bounding_box.bottom_right.y-bounding_box.top_left.y), SpaceRepresentation2D::SpaceType::Free)
{
  bounding_box_ = bounding_box;
  pose_.location.x = (bounding_box_.bottom_right.x - bounding_box_.top_left.x) / 2;
  pose_.location.y = (bounding_box_.bottom_right.y - bounding_box_.top_left.y) / 2;
  pose_.orientation = orientation;
}

