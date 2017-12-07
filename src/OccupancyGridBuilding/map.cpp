/**
 * Implementation of the Map class
 */
#include "map.h"
#include <random>
#include "map_tools_space_transformations.h"

Map::Map() : space_matrix_(default_map_size_x_, default_map_size_y_) {
  this->size_x_ = default_map_size_x_;
  this->size_y_ = default_map_size_y_;
  //Rooms should take up less than twenty percent of the maze
  this->max_room_size_x_ = (room_max_size_scale_factor_ * this->size_x_);
  this->max_room_size_y_ = (room_max_size_scale_factor_ * this->size_y_);
}

Map::Map(int max_space_x, int max_space_y) : space_matrix_(max_space_x, max_space_y) {
  this->size_x_ = max_space_x;
  this->size_y_ = max_space_y;
  this->max_room_size_x_ = (room_max_size_scale_factor_ * this->size_x_);
  this->max_room_size_y_ = (room_max_size_scale_factor_ * this->size_y_);
}

//TODO [issue #3] move this functionality to a factory class
void Map::GenerateMap() {

  int number_of_attempts = 0;
  const int max_attempts = 50;
  // TODO [issue #2] unify random number generation
  std::random_device rd;
  std::mt19937_64 random_number_generator(rd());
  std::uniform_int_distribution<> room_uniform_dist_x(1, this->max_room_size_x_);
  std::uniform_int_distribution<> room_uniform_dist_y(1, this->max_room_size_y_);
  std::uniform_int_distribution<> map_uniform_dist_x(1, this->size_x_);
  std::uniform_int_distribution<> map_uniform_dist_y(1, this->size_y_);
  std::tuple<int, int> potential_room_free_space;
  map_tools::geometry::Pose2D potential_room_pose;
  while (number_of_attempts <= max_attempts) {
    int x_free_space = room_uniform_dist_x(random_number_generator);
    int y_free_space = room_uniform_dist_y(random_number_generator);
    potential_room_free_space = std::tuple<int, int>(x_free_space, y_free_space);

    potential_room_pose.location.x = map_uniform_dist_x(random_number_generator);
    potential_room_pose.location.y = map_uniform_dist_y(random_number_generator);
    potential_room_pose.orientation = 0.0f; // Aligned x direction

    this->AddRoom(potential_room_free_space, potential_room_pose);
    number_of_attempts++;
  }

}

void Map::AddRoom(std::tuple<int, int> free_space, map_tools::geometry::Pose2D room_pose) {
  map_tools::geometry::Rectangle
      boundingBox = map_tools::space_transformations::GetBoundingBoxFromPoseAndSize(free_space, room_pose);

  if (!BoundingBoxIntersection(boundingBox) && BoundingBoxWithinMap(boundingBox)) {
    std::unique_ptr<RectangleRoom> new_room = std::make_unique<RectangleRoom>(boundingBox, room_pose.orientation);

//    for (auto const &line : new_room->GetRoomEdgesInMapFrame()) {
//      FillSpace(line.GetPointsOnLine());
//    }
//    room_vector_.push_back(std::move(new_room));

  } else {
    std::cout << "ROOM OVERLAP" << std::endl;
  }
}

bool Map::BoundingBoxWithinMap(const map_tools::geometry::Rectangle &new_bounding_box) {
  bool top_and_left_bound_ok = false;
  bool bottom_and_right_bound_ok = false;
  if (new_bounding_box.top_left.y > 0 && new_bounding_box.top_left.x > 0) {
    top_and_left_bound_ok = true;
  }

  if (new_bounding_box.bottom_right.x < size_x_ && new_bounding_box.bottom_right.y < size_y_) {
    bottom_and_right_bound_ok = true;
  }

  return top_and_left_bound_ok & bottom_and_right_bound_ok;

}

bool Map::BoundingBoxIntersection(const map_tools::geometry::Rectangle &potentialRoom) {
  bool anyIntersection = false;

  for (auto const &roomInVector : room_vector_) {

//    bool leftOfCurrentRoom = (roomInVector->GetBoundingBox().bottom_right.x < potentialRoom.top_left.x);
//    bool rightOfCurrentRoom = (roomInVector->GetBoundingBox().top_left.x > potentialRoom.bottom_right.x);
//    bool aboveCurrentRoom = (roomInVector->GetBoundingBox().bottom_right.y < potentialRoom.top_left.y);
//    bool belowCurrentRoom = (roomInVector->GetBoundingBox().top_left.y > potentialRoom.bottom_right.y);
//
//    if (leftOfCurrentRoom || rightOfCurrentRoom || aboveCurrentRoom || belowCurrentRoom) {
//      anyIntersection = false;
//    } else {
//      anyIntersection = true; // boxes overlap
//    }
  }
  return anyIntersection;
}

std::ostream &operator<<(std::ostream &os, Map const &map_instance) {
  os << map_instance.space_matrix_;
  return os;
}
