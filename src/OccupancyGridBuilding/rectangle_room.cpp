#include "rectangle_room.h"

RectangleRoom::RectangleRoom(int xFreeSpace, int yFreeSpace,const mapTools::Point& origin, const Map& mapToFill):
Room(mapToFill)
{
	this->xFreeSpace = xFreeSpace;
	this->yFreeSpace = yFreeSpace;
	this->origin = origin;
	populateMap();
}

RectangleRoom::~RectangleRoom(){
}

void RectangleRoom::populateMap(){
	std::vector<mapTools::Point> pointsToFill;
	mapTools::Point upperLeft;
	upperLeft.x = (origin.x - std::floor(xFreeSpace/2)) - 1;
	upperLeft.y = (origin.y - std::floor(yFreeSpace/2)) - 1;

	for(int i = upperLeft.x; i<=upperLeft.x + xFreeSpace; i++){
		mapTools::Point currentPoint;
		currentPoint.x = i;
		currentPoint.y = upperLeft.y;
		pointsToFill.push_back(currentPoint);
	}

	parentMap.fillSpace(pointsToFill);

}

