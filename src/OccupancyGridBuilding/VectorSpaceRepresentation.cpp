/**
 * @file VectorSpaceRepresentation.cpp
 * @author Eddy Scott
 */


#include "VectorSpaceRepresentation.h"


VectorSpaceRepresentation::VectorSpaceRepresentation(int xFreeSpace, int yFreeSpace) : 
spaceMatrix(xFreeSpace,std::vector<mapTools::SPACE_TYPE>(yFreeSpace))
{
}

mapTools::SPACE_TYPE& VectorSpaceRepresentation::operator()(int x, int y){
    /**
     * Ensure that the values we're trying to access are valid.  Note user's operate
     * in X,Y space which maps as follows:
     *          X =0, Y = 0 occurs at the upper left of the matrix
     *          X == column number
     *          Y == row number
     *
     */
    if(x < this->spaceMatrix[0].size() && y < this->spaceMatrix.size()
       && x > -1 && y > -1)
    {
        return this->spaceMatrix[y][x];
    }else{
        //TODO we should allow resizing of the map here
        //since we need to return a reference we return the reference to this class's invlaid type
        //HOWEVER, this means that a user could overwrite the invalid type since the return is not
        //const.  TODO fix this
        return this->_invalid_space;
    }

}


std::vector<mapTools::SPACE_TYPE> VectorSpaceRepresentation::row(int rowNum){
    return this->spaceMatrix[rowNum];
}
