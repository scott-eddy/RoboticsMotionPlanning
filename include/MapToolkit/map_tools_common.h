/**
 * @file common.h
 * @author Eddy Scott
 * @brief A common set of utilities that are used to generate a map
 */

#pragma once
#include <random>
namespace mapTools{

    /**
     * A structure that defines a 2D point in space
     */    
    struct Point{
		int x;
		int y;
            Point(){} //Default Ctor
                Point(int x, int y){
                this->x = x;
                this->y = y;
            }
	};

    /**
     * Definition of a rectangle by specifying two points.
     *
     * The two points make up the top left and upper right of the rectangle
     */
    struct Rect{
		Point topLeft;
		Point bottomRight;
	};

    /**
     * A useful definition of empty and free space
     */
    enum SPACE_TYPE{
        EMPTY = 0,
        OCCUPIED = 1,
        INVALID = 255 //MAX of uint8_t
    };

    /**
     * The cardinal directions.
     *
     * North represents motion in the +y direcetion
     * East represents motion in the +x direction
     * South represents motion in the -y direction
     * West represents motion in the -x direction
     */
    enum DIRECTION{
        NORTH,
        EAST,
        SOUTH,
        WEST,
        LAST
    };

}//mapTools
