/**
 * Implementation of the Map class
 */
#include "map.h"
#include <random>
Map::Map() : spaceMatrix(30, std::vector<uint8_t>(30)) {
  this->sizeX = 30; //Default map size
  this->sizeY = 30; //Default map size
  //Rooms should take up less than twenty percent of the maze
  this->maxRoomX = (0.2 * this->sizeX);
  this->maxRoomY = (0.2 * this->sizeY);
}

Map::Map(int sizeX, int sizeY) : spaceMatrix(sizeY, std::vector<uint8_t>(sizeX)) {
  this->sizeX = sizeX;
  this->sizeY = sizeY;
  this->maxRoomX = (0.2 * this->sizeX);
  this->maxRoomY = (0.2 * this->sizeY);
}

Map::~Map() {
}

void Map::generate() {

  int numberOfAttempts = 0;
  const int maxAttempts = 50;
  std::random_device rd;
  std::mt19937_64 randomNumGenerator(rd());
  std::uniform_int_distribution<> roomUniformX(1, this->maxRoomX);
  std::uniform_int_distribution<> roomUniformY(1, this->maxRoomY);
  std::uniform_int_distribution<> mapUniformX(1, this->sizeX);
  std::uniform_int_distribution<> mapUniformY(1, this->sizeY);
  std::tuple<int, int> curRoomFreeSpace;
  mapTools::Point curRoomOrigin;
  while (numberOfAttempts <= maxAttempts) {
    int xFreeSpace = roomUniformX(randomNumGenerator);
    int yFreeSpace = roomUniformY(randomNumGenerator);
    curRoomFreeSpace = std::tuple<int, int>(xFreeSpace, yFreeSpace);

    curRoomOrigin.x = mapUniformX(randomNumGenerator);
    curRoomOrigin.y = mapUniformY(randomNumGenerator);

    this->addRoom(curRoomFreeSpace, curRoomOrigin);
    numberOfAttempts++;
  }

}

void Map::addRoom(std::tuple<int, int> freeSpace, mapTools::Point origin) {
  mapTools::Rect boundingBox;
  boundingBox.topLeft.x = origin.x - std::get<0>(freeSpace) / 2;
  boundingBox.topLeft.y = origin.y - std::get<1>(freeSpace) / 2;

  boundingBox.bottomRight.x = origin.x + std::get<0>(freeSpace) / 2;
  boundingBox.bottomRight.y = origin.y + std::get<1>(freeSpace) / 2;

  if (!roomIntersection(boundingBox) && BoundingBoxWithinMap(boundingBox)) {
    std::unique_ptr<RectangleRoom>
        pRect(new RectangleRoom(std::get<0>(freeSpace), std::get<1>(freeSpace), origin, *this));
    roomVector.push_back(std::move(pRect));
  } else {
    std::cout << "ROOM OVERLAP" << std::endl;
  }
}

bool Map::BoundingBoxWithinMap(const mapTools::Rect &potentialRoom) {
  bool top_and_left_bound_ok = false;
  bool bottom_and_right_bound_ok = false;
  if (potentialRoom.topLeft.y > 0 && potentialRoom.topLeft.x > 0) {
    top_and_left_bound_ok = true;
  }

  if (potentialRoom.bottomRight.x < sizeX && potentialRoom.bottomRight.y < sizeY) {
    bottom_and_right_bound_ok = true;
  }

  return top_and_left_bound_ok & bottom_and_right_bound_ok;

}

void Map::addClutterToRoom(int roomNum) {
  if (roomNum >= 0 && roomNum < roomVector.size()) {
    roomVector[roomNum]->addClutter();
  }

}

bool Map::roomIntersection(const mapTools::Rect &potentialRoom) {
  bool anyIntersection = false;

  for (auto const &roomInVector : roomVector) {

    bool leftOfCurrentRoom = (roomInVector->getBoundingBox().bottomRight.x < potentialRoom.topLeft.x);
    bool rightOfCurrentRoom = (roomInVector->getBoundingBox().topLeft.x > potentialRoom.bottomRight.x);
    bool aboveCurrentRoom = (roomInVector->getBoundingBox().bottomRight.y < potentialRoom.topLeft.y);
    bool belowCurrentRoom = (roomInVector->getBoundingBox().topLeft.y > potentialRoom.bottomRight.y);

    if (leftOfCurrentRoom || rightOfCurrentRoom || aboveCurrentRoom || belowCurrentRoom) {
      anyIntersection = false; // room in vector is below current room
    } else {
      return true; // boxes overlap
    }
  }
  return anyIntersection;
}

void Map::fillSpace(std::vector<mapTools::Point> pointsToFill) const {
  for (auto const &currentPoint : pointsToFill) {
    if (currentPoint.y < sizeY && currentPoint.x < sizeX) {
      //N.B. y represents the row you are in and x represents the column
      spaceMatrix[currentPoint.y][currentPoint.x] = 1;
    } else {
      std::cout << "Doh!" << std::endl;
      //TODO: throw some error here?
    }
  }
}

void Map::printMatrix() {
  for (auto const &rowVect : spaceMatrix) {
    //rowVect is a reference to the spaceMatrix vector
    for (auto const &matrixValue : rowVect) {
      std::cout << static_cast<int>(matrixValue) << ",";
    }
    std::cout << std::endl;
  }
}

std::ostream &operator<<(std::ostream &os, Map const &mapObj) {
/**
	 * Print a row of "-"" at the top of the map
	 */
  for (auto const &i : mapObj.spaceMatrix[0]) {
    os << "-";
  }
  // Add an additional 2 "-" for the borders of the map
  os << "-" << "-" << std::endl;

  for (auto const &i : mapObj.spaceMatrix) {
    //i is a reference to the spaceMatrix vector
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
  for (auto col : mapObj.spaceMatrix[0]) {
    os << "-";
  }
  // Add an additional 2 "-" for the borders of the map
  os << "-" << "-" << std::endl;
  return os;
}
