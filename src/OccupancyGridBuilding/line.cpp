
#include "line.h"
Line::Line(std::vector<map_tools::geometry::Point2D> points_to_connect) : points_on_line_(0) {
  this->FindPointsOnLine(points_to_connect);
}

std::vector<map_tools::geometry::Point2D> Line::GetPointsOnLine() const {
  return this->points_on_line_;
}

void Line::FindPointsOnLine(std::vector<map_tools::geometry::Point2D> points_to_connect) {
  points_on_line_.clear();
  if (points_to_connect[0].y == points_to_connect[1].y) {
    //Horizontal line
    int difference = points_to_connect[0].x - points_to_connect[1].x;
    int numToFill = std::fabs(difference);
    int xStartLocation = std::min(points_to_connect[0].x, points_to_connect[1].x);
    for (int i = xStartLocation; i <= xStartLocation + numToFill; i++) {
      map_tools::geometry::Point2D currentPoint;
      currentPoint.y = points_to_connect[0].y;
      currentPoint.x = i;
      points_on_line_.push_back(currentPoint);
    }
  } else if (points_to_connect[0].x == points_to_connect[1].x) {
    //Vertical line
    int difference = points_to_connect[0].y - points_to_connect[1].y;
    int numToFill = std::fabs(difference);
    int yStartLocation = std::min(points_to_connect[0].y, points_to_connect[1].y);
    for (int i = yStartLocation; i <= yStartLocation + numToFill; i++) {
      map_tools::geometry::Point2D currentPoint;
      currentPoint.y = i;
      currentPoint.x = points_to_connect[0].x;
      points_on_line_.push_back(currentPoint);
    }
  } else {
    //Assumed to be best straight line
  }
}