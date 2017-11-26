/**
 * Implementation of the Map class
 */
#include "map.h"
#include <random>
Map::Map() : space_matrix_(30, std::vector<uint8_t>(30)) {
  this->size_x_ = 30; //Default map size
  this->size_y_ = 30; //Default map size
  //Rooms should take up less than twenty percent of the maze
  this->max_room_size_x_ = (0.2 * this->size_x_);
  this->max_room_size_y_ = (0.2 * this->size_y_);
}

Map::Map(int max_space_x, int max_space_y) : space_matrix_(max_space_y, std::vector<uint8_t>(max_space_x)) {
  this->size_x_ = max_space_x;
  this->size_y_ = max_space_y;
  this->max_room_size_x_ = (0.2 * this->size_x_);
  this->max_room_size_y_ = (0.2 * this->size_y_);
}

void Map::GenerateMap() {

  int numberOfAttempts = 0;
  const int maxAttempts = 50;
  std::random_device rd;
  std::mt19937_64 randomNumGenerator(rd());
  std::uniform_int_distribution<> roomUniformX(1, this->max_room_size_x_);
  std::uniform_int_distribution<> roomUniformY(1, this->max_room_size_y_);
  std::uniform_int_distribution<> mapUniformX(1, this->size_x_);
  std::uniform_int_distribution<> mapUniformY(1, this->size_y_);
  std::tuple<int, int> curRoomFreeSpace;
  map_tools::geometry::Point2D curRoomOrigin;
  while (numberOfAttempts <= maxAttempts) {
    int xFreeSpace = roomUniformX(randomNumGenerator);
    int yFreeSpace = roomUniformY(randomNumGenerator);
    curRoomFreeSpace = std::tuple<int, int>(xFreeSpace, yFreeSpace);

    curRoomOrigin.x = mapUniformX(randomNumGenerator);
    curRoomOrigin.y = mapUniformY(randomNumGenerator);

    this->AddRoom(curRoomFreeSpace, curRoomOrigin);
    numberOfAttempts++;
  }

}

void Map::AddRoom(std::tuple<int, int> free_space, map_tools::geometry::Point2D origin) {
  map_tools::geometry::Rectangle boundingBox;
  boundingBox.top_left_.x = origin.x - std::get<0>(free_space) / 2;
  boundingBox.top_left_.y = origin.y - std::get<1>(free_space) / 2;

  boundingBox.bottom_right_.x = origin.x + std::get<0>(free_space) / 2;
  boundingBox.bottom_right_.y = origin.y + std::get<1>(free_space) / 2;

  if (!BoundingBoxIntersection(boundingBox) && BoundingBoxWithinMap(boundingBox)) {
    std::unique_ptr<RectangleRoom>
        pRect(new RectangleRoom(std::get<0>(free_space), std::get<1>(free_space), origin));
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

void Map::AddClutterToRoom(int room_number) {
  if (room_number >= 0 && room_number < room_vector_.size()) {
    room_vector_[room_number]->AddClutter();
  }

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

void Map::FillSpace(std::vector<map_tools::geometry::Point2D> points_to_fill) const {
  for (auto const &currentPoint : points_to_fill) {
    if (currentPoint.y < size_y_ && currentPoint.x < size_x_) {
      //N.B. y represents the row you are in and x represents the column
      space_matrix_[currentPoint.y][currentPoint.x] = 1;
    } else {
      std::cout << "Doh!" << std::endl;
      //TODO: throw some error here?
    }
  }
}

void Map::PrintMatrix() {
  for (auto const &rowVect : space_matrix_) {
    //rowVect is a reference to the space_matrix_ vector
    for (auto const &matrixValue : rowVect) {
      std::cout << static_cast<int>(matrixValue) << ",";
    }
    std::cout << std::endl;
  }
}

std::ostream &operator<<(std::ostream &os, Map const &map_instance) {
/**
	 * Print a row of "-"" at the top of the map
	 */
  for (auto const &i : map_instance.space_matrix_[0]) {
    os << "-";
  }
  // Add an additional 2 "-" for the borders of the map
  os << "-" << "-" << std::endl;

  for (auto const &i : map_instance.space_matrix_) {
    //i is a reference to the space_matrix_ vector
    os << "|";
    for (auto const &j : i) {
      //j is the value in the
      if (j == 0) {
        os << " ";
      } else if (j == 1) {
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
  for (auto col : map_instance.space_matrix_[0]) {
    os << "-";
  }
  // Add an additional 2 "-" for the borders of the map
  os << "-" << "-" << std::endl;
  return os;
}
