/*

----------------------------------------
*/

#pragma once
#include "room.h"
#include <cmath>
/**
 * @brief Abstract class defining what makes up a Room in a map
 * @details [long description]
 * 
 */
class RectangleRoom : public Room{
public:
	RectangleRoom(int xFreeSpace, int yFreeSpace, const mapTools::Point& origin, const Map& parentMap);
	~RectangleRoom();

private:
	void populateMap();
};