
#include "line.h"
Line::Line(std::vector<mapTools::Point> pointsToConnect) : pointsOnLine(0) {
  this->findPointsOnLine(pointsToConnect);
}
Line::~Line() {}

std::vector<mapTools::Point> Line::getPointsOnLine() const {
  return this->pointsOnLine;
}

void Line::findPointsOnLine(std::vector<mapTools::Point> pointsToConnect) {
  pointsOnLine.clear();
  if (pointsToConnect[0].y == pointsToConnect[1].y) {
    //Horizontal line
    int difference = pointsToConnect[0].x - pointsToConnect[1].x;
    int numToFill = std::fabs(difference);
    int xStartLocation = std::min(pointsToConnect[0].x, pointsToConnect[1].x);
    for (int i = xStartLocation; i <= xStartLocation + numToFill; i++) {
      mapTools::Point currentPoint;
      currentPoint.y = pointsToConnect[0].y;
      currentPoint.x = i;
      pointsOnLine.push_back(currentPoint);
    }
  } else if (pointsToConnect[0].x == pointsToConnect[1].x) {
    //Vertical line
    int difference = pointsToConnect[0].y - pointsToConnect[1].y;
    int numToFill = std::fabs(difference);
    int yStartLocation = std::min(pointsToConnect[0].y, pointsToConnect[1].y);
    for (int i = yStartLocation; i <= yStartLocation + numToFill; i++) {
      mapTools::Point currentPoint;
      currentPoint.y = i;
      currentPoint.x = pointsToConnect[0].x;
      pointsOnLine.push_back(currentPoint);
    }
  } else {
    //Assumed to be best straight line
  }
}