/**
 * @brief A room that is rectangular in shape
 * @details A class that fills the space matrix of its parent map
 *          with 4 walls and randomly generated clutter
 * 
 * @author Eddy Scott
 */

#include "rectangle_room.h"
#include <random> //Needed to add clutter to a room
RectangleRoom::RectangleRoom(int xFreeSpace, int yFreeSpace, const map_tools::geometry::Point2D &origin) {
  this->x_free_space_ = xFreeSpace;
  this->y_free_space_ = yFreeSpace;
  this->origin = origin;

  upper_left_.x = (origin.x - xFreeSpace / 2) - 1;
  upper_left_.y = (origin.y - yFreeSpace / 2) - 1;

  lower_right_.x = (origin.x + xFreeSpace / 2) - 1;
  lower_right_.y = (origin.y + yFreeSpace / 2) - 1;

  PopulateMap();
}

void RectangleRoom::PopulateMap() {
  //Generate the remaining points to define the entire border of the map
  map_tools::geometry::Point2D upperRight;
  upperRight.x = (origin.x + x_free_space_ / 2) - 1;
  upperRight.y = (origin.y - y_free_space_ / 2) - 1;

  map_tools::geometry::Point2D lowerLeft;
  lowerLeft.x = (origin.x - x_free_space_ / 2) - 1;
  lowerLeft.y = (origin.y + y_free_space_ / 2) - 1;

  std::vector<Line> roomBorder;

  Line topLine(std::vector<map_tools::geometry::Point2D>({upper_left_, upperRight}));
  Line bottomLine(std::vector<map_tools::geometry::Point2D>({lowerLeft, lower_right_}));
  Line leftLine(std::vector<map_tools::geometry::Point2D>({upper_left_, lowerLeft}));
  Line rightLine(std::vector<map_tools::geometry::Point2D>({upperRight, lower_right_}));

  roomBorder.push_back(topLine);
  roomBorder.push_back(bottomLine);
  roomBorder.push_back(leftLine);
  roomBorder.push_back(rightLine);

  // TODO propogate this info back up
  //for (auto const &currentLine : roomBorder) {
  //  parentMap.FillSpace(currentLine.GetPointsOnLine());
  //}
}

map_tools::geometry::Rectangle RectangleRoom::GetBoundingBox() {
  map_tools::geometry::Rectangle boundingBox;
  boundingBox.top_left_.x = origin.x - std::floor(x_free_space_ / 2);
  boundingBox.top_left_.y = origin.y - std::floor(y_free_space_ / 2);

  boundingBox.bottom_right_.x = origin.x + std::floor(x_free_space_ / 2);
  boundingBox.bottom_right_.y = origin.y + std::floor(y_free_space_ / 2);

  return boundingBox;
}

void RectangleRoom::AddClutter() {
  std::random_device rd;
  std::mt19937_64 randomNumGenerator(rd());

  int mean = 0;
  int stdDev = 1;
  std::normal_distribution<> dis(mean, stdDev);
  auto twoSigma = mean - (2 * stdDev);

  std::vector<map_tools::geometry::Point2D> points_to_fill;

  for (int i = upper_left_.x; i <= lower_right_.x; i++) {
    for (int j = upper_left_.y; j <= lower_right_.y; j++) {
      auto random_number = dis(randomNumGenerator);
      //std::cout << "Random Number: " << random_number << std::endl;

      if (random_number < (mean - stdDev)) {
        map_tools::geometry::Point2D filledSpace;
        filledSpace.x = i;
        filledSpace.y = j;
        points_to_fill.push_back(filledSpace);
      }

    }
  }

  //TODO propogate this info back up
//  parentMap.FillSpace(points_to_fill);

}

