/**
 * Implementation of the Map class
 */
#include "map.h"
#include <random>
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
  map_tools::geometry::Point2D potential_room_origin;
  while (number_of_attempts <= max_attempts) {
    int x_free_space = room_uniform_dist_x(random_number_generator);
    int y_free_space = room_uniform_dist_y(random_number_generator);
    potential_room_free_space = std::tuple<int, int>(x_free_space, y_free_space);

    potential_room_origin.x = map_uniform_dist_x(random_number_generator);
    potential_room_origin.y = map_uniform_dist_y(random_number_generator);

    this->AddRoom(potential_room_free_space, potential_room_origin);
    number_of_attempts++;
  }

}

void Map::AddRoom(std::tuple<int, int> free_space, map_tools::geometry::Point2D origin) {
  map_tools::geometry::Rectangle boundingBox;
  //TODO [issue #4] this transform should be defined and likely a member of SpaceRepresentation2D
  boundingBox.top_left_.x = origin.x - std::get<0>(free_space) / 2;
  boundingBox.top_left_.y = origin.y - std::get<1>(free_space) / 2;

  boundingBox.bottom_right_.x = origin.x + std::get<0>(free_space) / 2;
  boundingBox.bottom_right_.y = origin.y + std::get<1>(free_space) / 2;

  if (!BoundingBoxIntersection(boundingBox) && BoundingBoxWithinMap(boundingBox)) {
    //TODO std::make_unique
    std::unique_ptr<RectangleRoom>
        pRect(new RectangleRoom(boundingBox));

    for (auto const &line : pRect->GetRoomEdgesInMapFrame()) {
      FillSpace(line.GetPointsOnLine());
    }
    room_vector_.push_back(std::move(pRect));

  } else {
    std::cout << "ROOM OVERLAP" << std::endl;
  }
}

bool Map::BoundingBoxWithinMap(const map_tools::geometry::Rectangle &new_bounding_box) {
  bool top_and_left_bound_ok = false;
  bool bottom_and_right_bound_ok = false;
  if (new_bounding_box.top_left_.y > 0 && new_bounding_box.top_left_.x > 0) {
    top_and_left_bound_ok = true;
  }

  if (new_bounding_box.bottom_right_.x < size_x_ && new_bounding_box.bottom_right_.y < size_y_) {
    bottom_and_right_bound_ok = true;
  }

  return top_and_left_bound_ok & bottom_and_right_bound_ok;

}

bool Map::BoundingBoxIntersection(const map_tools::geometry::Rectangle &potentialRoom) {
  bool anyIntersection = false;

  for (auto const &roomInVector : room_vector_) {

    bool leftOfCurrentRoom = (roomInVector->GetBoundingBox().bottom_right_.x < potentialRoom.top_left_.x);
    bool rightOfCurrentRoom = (roomInVector->GetBoundingBox().top_left_.x > potentialRoom.bottom_right_.x);
    bool aboveCurrentRoom = (roomInVector->GetBoundingBox().bottom_right_.y < potentialRoom.top_left_.y);
    bool belowCurrentRoom = (roomInVector->GetBoundingBox().top_left_.y > potentialRoom.bottom_right_.y);

    if (leftOfCurrentRoom || rightOfCurrentRoom || aboveCurrentRoom || belowCurrentRoom) {
      anyIntersection = false; // room in vector is below current room
    } else {
      return true; // boxes overlap
    }
  }
  return anyIntersection;
}

void Map::FillSpace(std::vector<map_tools::geometry::Point2D> points_to_fill) {
  for (auto const &currentPoint : points_to_fill) {
    if (currentPoint.y < size_y_ && currentPoint.x < size_x_) {
      //N.B. y represents the row you are in and x represents the column
      space_matrix_(currentPoint.x, currentPoint.y) = SpaceRepresentation2D::SpaceType::Occupied;
    } else {
      std::cout << "Doh!" << std::endl;
      //TODO: throw some error here?
    }
  }
}

std::ostream &operator<<(std::ostream &os, Map const &map_instance) {
  /**
	 * Print a row of "-"" at the top of the map
	 */
  for (auto const &i : map_instance.space_matrix_.GetSpaceAsMatrix()[0]) {
    os << "-";
  }
  //Add an additional 2 "-" for the borders of the map
  os << "-" << "-" << std::endl;

  for (auto const &i : map_instance.space_matrix_.GetSpaceAsMatrix()) {
    //i is a reference to the space_matrix_ vector
    os << "|";
    for (auto const &j : i) {
      //j is the value in the
      if (j == SpaceRepresentation2D::SpaceType::Free) {
        os << " ";
      } else if (j == SpaceRepresentation2D::SpaceType::Occupied) {
        os << "*";
      }

      //! check if j is at the end of the current vector.
      if (&j == &i.back()) {
        os << "|";
      }
    }
    os << std::endl;
  }


  /**
   * Print a row of -- at the bottom of the map
   */
  for (auto col : map_instance.space_matrix_.GetSpaceAsMatrix()[0]) {
    os << "-";
  }
  //Add an additional 2 "-" for the borders of the map
  os << "-" << "-" << std::endl;
  return os;
}
