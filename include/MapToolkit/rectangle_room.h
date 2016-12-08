/**
 * @file rectangle_room.h
 * @author Eddy Scott
 * @brief Concrete class that implements the methods in the Room class
 */

#pragma once
#include "room.h"

class RectangleRoom : public Room{
public:
    RectangleRoom(int xFreeSpace, int yFreeSpace, const mapTools::Point& origin, const Map& parentMap);
    ~RectangleRoom();
    mapTools::Rect getBoundingBox();
    
    void addClutter();
    void fill(mapTools::SPACE_TYPE typeToFill);
private:
	void populateMap();
	mapTools::Point upperLeft;
	mapTools::Point	lowerRight;

};
