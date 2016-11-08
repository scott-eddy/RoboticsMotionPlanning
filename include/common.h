
#pragma once

namespace mapTools{
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
     * Definition of a rectangle by specifying two points
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
        OCCUPIED = 1
    };

    enum DIRECTION{
        NORTH,
        EAST,
        SOUTH,
        WEST,
        LAST
    };
}
