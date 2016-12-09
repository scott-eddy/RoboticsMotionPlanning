/**
 * @file VectorSpaceRepresentation.h
 * @author Eddy Scott
 * @brief concrete class implementing SpaceRepresentation with std::vector
 */

#pragma once
#include "SpaceRepresentation.h"
#include "map_tools_common.h"
#include <vector>
class VectorSpaceRepresentation : public SpaceRepresentation {
public:
    /**
     * Ctor that defines the vector size
     */
    VectorSpaceRepresentation(int xFreeSpace, int yFreeSpace);

    /**
     * Default detor
     */
    ~VectorSpaceRepresentation(){};
    /**
     * Returns a vector of the row specified by rowNumber (zero indexed).
     */
    std::vector<mapTools::SPACE_TYPE> row(int rowNumber);

    /**
     * Returns a vector of the column spefified by colNumber (zero indexed).
     */
    //std::vector<mapTools::Space_TYPE> col(int colNumber);

    /**
     * Needed for range based for loops
     */
    //int * begin(); 

    /**
     * Needed for range based for loops
     */
    //int * end();

        
    mapTools::SPACE_TYPE& operator()(int x, int y);


    /**
     * This is a hack around returning a reference with operator().  Needs to be 
     * thought out more.  See TODO in cpp file
     */
    mapTools::SPACE_TYPE _invalid_space = mapTools::SPACE_TYPE::INVALID;

private:

    /**
     * This Space representation holds the space data in a matrix that
     * is composed of two std::vector's
     */
    std::vector<std::vector<mapTools::SPACE_TYPE>> spaceMatrix;


};
