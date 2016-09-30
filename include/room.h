/*
----------------------------------------
****************      ******************
*  Empty Room  *      * Cluttered Room *
*			   ********     **     *   *
*                 ???           **     *
*****************    *******************
*                                      *
*          Large Empty Room            *
*                                      *
****************************************
----------------------------------------
*/

#pragma once
#include "map.h"
#include "common.h"
//Forward declaration of map class
class Map;
/**
 * @brief Abstract class defining what makes up a Room in a map
 * @details [long description]
 * 
 */
class Room{
public:
	virtual ~Room() = 0;
	//virtual void addWall(const Wall& wallToAdd) = 0;

protected:
	Room(const Map& map) : parentMap(map){};
	virtual void populateMap() = 0;
	const Map& parentMap;
	int xFreeSpace;
	int yFreeSpace;
	mapTools::Point origin;
};

inline Room::~Room() { }