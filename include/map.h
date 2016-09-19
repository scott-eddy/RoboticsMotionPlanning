/**
 * This is a class that defines a map.  A map is composed of 
 * free space and occupied space a-la an occupancy grid
 *
*/

#pragma once
#include <vector>
#include <iostream>

class Map{
public:
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
	std::vector<std::vector<uint8_t> > spaceMatrix;

	int debug_value;

	/**
	 * @brief prints the elements of the space matrix
	 * @details Prints spaceMatrix out the the terminal
	 *          with * == occupied space
	 *              "" == free space
	 * 
	 * @param os [description]
	 * @param mapObj map to print
	 */
	friend std::ostream &operator<<(std::ostream &os,Map const &mapObj);
};