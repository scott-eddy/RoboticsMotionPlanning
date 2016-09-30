/**
 * This is a class that defines a map.  A map is composed of 
 * free space and occupied space a-la an occupancy grid
 *
*/

#pragma once
#include <vector>
#include <iostream>
#include "common.h"
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
	friend std::ostream &operator<<(std::ostream &os,Map const &mapObj);

	/**
	 * @brief initializes a room and stores a pointer of it
	 * @details Not typically needed, as all information for each room is stored
	 *          in the space matrix of this class.  However, in the future having access
	 *          to rooms might be handy
	 * 
	 * @param 
	 * @param origin [description]
	 */
	void addRoom(std::tuple<int,int> freeSpace, mapTools::Point origin);

	void fillSpace(std::vector<mapTools::Point> pointsToFill) const;

	void printMatrix();

private:
	int sizeX;
	int sizeY;
	std::vector<std::unique_ptr<Room>> roomVector;
};