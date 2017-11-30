#pragma once
#include <vector>
#include "map_tools_geometry.h"
#include <cmath>
namespace map_tools::geometry {
class Line {
 public:
  Line(std::vector<map_tools::geometry::Point2D> points_to_connect);
  ~Line() = default;
  std::vector<map_tools::geometry::Point2D> GetPointsOnLine() const;

 private:
  std::vector<map_tools::geometry::Point2D> points_on_line_;
  void FindPointsOnLine(std::vector<map_tools::geometry::Point2D> points_to_connect);
};
}