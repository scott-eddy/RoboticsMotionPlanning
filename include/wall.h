
#pragma once
#include "map_tools_geometry.h"
class Wall {
 public:
  Wall();
  ~Wall();

  map_tools::geometry::Point2D startPoint;
  map_tools::geometry::Point2D endPoint;
};