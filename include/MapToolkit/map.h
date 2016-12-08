/**
 * @file map.h
 * @author Eddy Scott
 * @brief This is a class that defines a map.  
 *
 * A map is composed of free space and occupied space a-la an occupancy grid.  This data
 * is housed in the spaceMatrix 
*/

#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "map_tools_common.h"
#include "room.h"
#include "rectangle_room.h"

//Forward declaration of room
class Room;

class Map{
public:
	/**
	 * @brief Default constructor
	 * @details makes a map of default size [30x30]
	 */
	Map();

	/**
	 * @brief Constructor of th map
	 * @details Generates the matrix of free and occupied space
	 * 
	 * @param sizeX the maximum size of the map in the x direction
	 * @param sizeY the maximum size of the map in the y direction
	 */
	Map(int sizeX, int sizeY);

	/**
	 * @brief Destructor of map
	 */
	~Map();

	//! Represent a matrix as a vector of vectors.  
	//! Could be done with template matrix class ala Eigen
        //! mutable such that it can be altered from the const functions
	mutable std::vector<std::vector<uint8_t> > spaceMatrix;

	/**
 	* @brief Prints the map as ASCII 
 	* @details Prints a representation of the map with free space
 	*          printed as " " and occupied space printed with "*"
 	*          The map is bordered with "-" at top and bottom and "|"
 	*          on either side
 	* 
 	* @param os ostream to be printed to 
 	* @param mapObj map object to be printed out
 	*/
	friend std::ostream &operator<<(std::ostream &os,const Map &mapObj);

	/**
	 * @brief initializes a room and stores a pointer of it
	 * @details Not typically needed, as all information for each room is stored
	 *          in the space matrix of this class.  However, in the future having access
	 *          to rooms might be handy.
         *          
         *          A room is thusly specified as: 
         *          right most wall: origin.x + (std::get<0>(freeSpace))/2
	 *          left most wall: origin.x - (std::get<0>(freeSpace))/2
         *
         *          top most wall: origin.y - (std::get<1>(freeSpace))/2 [Note the use of the minus since 0 index is at top of space matrix]
         *          bottom most wall: origin.y + (std::get<1>(freeSpace))/2 
	 * @param freeSpace a pair of numbers representing the x and y free space of the room 
	 * @param origin the x,y location of the rooms origin
	 */
	bool addRoom(std::tuple<int,int> freeSpace, mapTools::Point origin);

	/**
	 * @brief Fills the map's space matrix by setting the x,y locations in pointsToFill to mapTools::SPACE_TYPE::OCCUPIED
	 *
	 */
	void fillSpace(std::vector<mapTools::Point> pointsToFill) const;


        /**
         * @brief Fills the point in the map's space matrix by setting the x,y locations to mapTools::SPACE_TYPE::OCCUPIED
         */
        void fillSpace(mapTools::Point pointToFill) const;

	/**
	 * @brief Fills the map's space matrix by setting the x,y locations in pointsToFill to mapTools::SPACE_TYPE::EMPTY 
	 *
	 */
	void emptySpace(std::vector<mapTools::Point> pointsToFill) const;
	
        /** 
	 * @brief Prints the numerical representation of the Map's space matrix
	 *
	 */
	void printMatrix();

	/**
	 * @brief returns true if two rooms in the map intersect one another
	 */
	bool roomIntersection(const mapTools::Rect &potentialRoom);

	/**
	 * @brief Fills space inside of a room
	 *
	 */
	void addClutterToRoom(int roomNum);
	
	/**
	 * @brief Populates a map with rooms and passageways
	 * TODO move this functionality to a factory class
	 */ 
	void generate();

private:
	int sizeX;
	int sizeY;
	int maxRoomX;
	int maxRoomY;
	std::vector<std::unique_ptr<Room>> roomVector;
    
    /**
     * @brief loops through spaceMatrix and fills space acording to a growing tree algorithm
     */
    void makeMaze();

    /**
     * @brief Makes perfect mazes in passage ways by carving space in directions
     * 
     */
    void growTree(int x, int y);

    /**
     * @brief returns the directions to mapTools::SPACE_TYPE from the root point.  Example: if you are at (0,0) and the space at (0,1) is of type SPACE_TYPE
     *        the function will return EAST
     */
    void findAdjacentSpace(const mapTools::Point &root, const mapTools::SPACE_TYPE &spaceType,std::vector<mapTools::DIRECTION> &directionToSpaceType);
    
    /**
     * @brief same as it's base implementation but requires numberOfTiles of free space in order to return a direction.
     */
    void findAdjacentSpace(const int numberOfTiles, const mapTools::Point &root, const mapTools::SPACE_TYPE &spaceType,std::vector<mapTools::DIRECTION> &directionToSpaceType);

    /**
     * @brief fills the space in the direction specified by directionToFill away from the root point.
     */
    mapTools::Point fillAdjacentSpace(const mapTools::Point &root, const mapTools::DIRECTION &directionToFill); 
   
    /**
     * @brief returns the point in the direction specified by directionToFill from the root point
     */ 
    mapTools::Point moveToAdjacentSpace(const mapTools::Point &root, const mapTools::DIRECTION &directionToFill);

    /**
     * @briefs move some amount of space in a single direction away from the root point.
     */
    mapTools::Point moveConsecutiveSpace(const int numSpace,const mapTools::Point &root, const mapTools::DIRECTION &directionToFill);
};
