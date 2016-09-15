/**
 * This is a class that defines a map.  A map is composed of 
 * free space and occupied space a-la an occupancy grid
 *
*/

#pragma once
#include <vector>

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
	std::vector<std::vector<int> > spaceMatrix;

};