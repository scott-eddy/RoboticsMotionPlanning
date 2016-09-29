#include "rectangle_room.h"

RectangleRoom::RectangleRoom(int xFreeSpace, int yFreeSpace,const mapTools::Point& origin, const Map& mapToFill):
Room(mapToFill)
{
	this->xFreeSpace = xFreeSpace;
	this->yFreeSpace = yFreeSpace;
	this->origin = origin;
}

RectangleRoom::~RectangleRoom(){
}

void RectangleRoom::fillSpace(){
	
}

