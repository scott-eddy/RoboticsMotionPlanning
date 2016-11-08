/*

----------------------------------------
*/

#pragma once
#include "room.h"
#include <cmath>
#include "line.h"
/**
 * @brief Abstract class defining what makes up a Room in a map
 * @details [long description]
 * 
 */
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
