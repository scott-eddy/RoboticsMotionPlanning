/**
 * @file SpaceRepresentation.h
 * @author Eddy Scott
 * @brief A class that abstracts away how space is stored in a matrix
 */

#pragma once
#include "map_tools_common.h"
class SpaceRepresentation{
public:
    /**
     * Virtual destructor
     */
    virtual ~SpaceRepresentation(){};

    /**
     * Pure virtual overloading of operator() for two parameters.
     *
     * This is how users access the data in the SpaceRepresentation.  Note that
     * operator[] was not overloaded as this adds a fair amount of complexity
     */ 
    virtual mapTools::SPACE_TYPE operator()(int x, int y) = 0;

};
