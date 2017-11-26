#pragma once
#include <vector>
#include "map_tools_geometry.h"
#include <cmath>

class Line {
 public:
  Line(std::vector<map_tools::geometry::Point2D> pointsToConnect);
  ~Line();
  std::vector<map_tools::geometry::Point2D> getPointsOnLine() const;

 private:
  std::vector<map_tools::geometry::Point2D> pointsOnLine;
  void findPointsOnLine(std::vector<map_tools::geometry::Point2D> pointsToConnect);
};