//
// Created by Eddy Scott on 11/26/17.
//

#include "space_representation_2D.h"

SpaceRepresentation2D::SpaceRepresentation2D(int size_x_dir, int size_y_dir) : space_matrix_(size_y_dir, std::vector<SpaceType>(size_x_dir)){

}

SpaceRepresentation2D::SpaceType& SpaceRepresentation2D::operator()(size_t row, size_t column){
  return space_matrix_[column][row];
}

const SpaceRepresentation2D::SpaceType& SpaceRepresentation2D::operator()(size_t row, size_t column) const{
  return space_matrix_[column][row];
}
