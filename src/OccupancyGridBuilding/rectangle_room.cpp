#include "rectangle_room.h"

RectangleRoom::RectangleRoom(int xFreeSpace, int yFreeSpace,const mapTools::Point& origin, const Map& parentMap):
Room(parentMap)
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

	std::vector<Line> roomBorder;

	Line topLine(std::vector<mapTools::Point>({upperLeft,upperRight}));
	Line bottomLine(std::vector<mapTools::Point>({lowerLeft,lowerRight}));
	Line leftLine(std::vector<mapTools::Point>({upperLeft,lowerLeft}));
	Line rightLine(std::vector<mapTools::Point>({upperRight,lowerRight}));

	roomBorder.push_back(topLine);
	roomBorder.push_back(bottomLine);
	roomBorder.push_back(leftLine);
	roomBorder.push_back(rightLine);

	for(auto const &currentLine : roomBorder){
		parentMap.fillSpace(currentLine.getPointsOnLine());
	}
}

mapTools::Rect RectangleRoom::getBoundingBox(){
	mapTools::Rect boundingBox;
	boundingBox.topLeft.x = origin.x - std::floor(xFreeSpace/2);
	boundingBox.topLeft.y = origin.y - std::floor(yFreeSpace/2);

	boundingBox.bottomRight.x = origin.x + std::floor(xFreeSpace/2);
	boundingBox.bottomRight.y = origin.y + std::floor(yFreeSpace/2);

	return boundingBox;

}

