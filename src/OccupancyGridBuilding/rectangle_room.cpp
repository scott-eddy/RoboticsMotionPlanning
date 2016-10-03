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

	mapTools::Point upperRight;
	upperRight.x = (origin.x + std::floor(xFreeSpace/2)) - 1;
	upperRight.y = (origin.y - std::floor(yFreeSpace/2)) - 1;

	mapTools::Point lowerLeft;
	lowerLeft.x = (origin.x - std::floor(xFreeSpace/2)) - 1;
	lowerLeft.y = (origin.y + std::floor(yFreeSpace/2)) - 1;

	mapTools::Point lowerRight;
	lowerRight.x = (origin.x + std::floor(xFreeSpace/2)) - 1;
	lowerRight.y = (origin.y + std::floor(yFreeSpace/2)) - 1;



}

