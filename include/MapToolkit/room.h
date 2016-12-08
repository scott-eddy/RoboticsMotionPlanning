/**
 * @file room.h
 * @author Eddy Scott
 * @brief a base class that defines a room
 *
 * The intent is that a room is a location in a Map's Space Matrix that contains 
 * either free or occupied space.  Rooms can be rectangular, circular, oblong, etc.
 */

#pragma once
#include "map.h"
#include "map_tools_common.h"

//Forward declaration of map class
class Map;

class Room{
public:
    /**
     * Pure virtual destructor
     */	
    virtual ~Room() = 0;
    
    /**
     * Returns the bounding box of a room.
     *
     * Even if a room is non-rectangular it should fit in a 2D rectangualr bounding 
     * box
     */
    virtual mapTools::Rect getBoundingBox() = 0;
    
    /**
     * Generates clutter in the room by making space within the mapTools::SPACE_TYPE::OCCUPIED
     */
    virtual void addClutter() = 0;
    
    /**
     * Fills the entire room to the space type specified.
     *
     * @param typeToFill the Space type that the room should be filled to
     */
    virtual void fill(mapTools::SPACE_TYPE typeToFill) = 0;
protected:
    
    /**
     * Constructor, specifies the map that this room is a part of.
     */
    Room(const Map& map) : parentMap(map){};
    
    /**
     * populate's the parent map's space matrix with SPACE_TYPE values for this room.
     */
    virtual void populateMap() = 0;
    
    /**
     * The map that this room is a part of.
     */
    const Map& parentMap;
    
    /**
     * The total amount of space this room has in the X direction.
     */
    int xFreeSpace;
    
    /**
     * The total amount of space this room has in the Y direction.
     */
    int yFreeSpace;
    
    /**
     * The point at the geometric center of this room.
     */
    mapTools::Point origin;
};
/**
 * Needed to make the pure virtual destructor valid
 */
inline Room::~Room() { }
