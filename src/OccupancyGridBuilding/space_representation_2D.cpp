//
// Created by Eddy Scott on 11/26/17.
//

#include <ostream>
#include "space_representation_2D.h"

SpaceRepresentation2D::SpaceRepresentation2D(size_t size_x_dir, size_t size_y_dir) :
    space_matrix_(size_y_dir, std::vector<SpaceType>(size_x_dir, SpaceRepresentation2D::SpaceType::Unknown)){

  size_x_dir_ = size_x_dir;
  size_y_dir_ = size_y_dir;
}

SpaceRepresentation2D::SpaceRepresentation2D(size_t size_x_dir, size_t size_y_dir, SpaceRepresentation2D::SpaceType defualt_space_fill) :
  space_matrix_(size_y_dir, std::vector<SpaceType>(size_x_dir, defualt_space_fill)) {
}

SpaceRepresentation2D::SpaceType& SpaceRepresentation2D::operator()(size_t x_location, size_t y_location){
  return space_matrix_[y_location][x_location];
}

const SpaceRepresentation2D::SpaceType& SpaceRepresentation2D::operator()(size_t x_location, size_t y_location) const{
  return space_matrix_[y_location][x_location];
}

const std::vector<std::vector<SpaceRepresentation2D::SpaceType>>& SpaceRepresentation2D::GetSpaceAsMatrix() const {
  return space_matrix_;
}

std::ostream &operator<<(std::ostream &os, const SpaceRepresentation2D& space_instance){
  /**
	 * Print a row of "-"" at the top of the space
	 */
  for (auto const &i : space_instance.space_matrix_[0]) {
    os << "-";
  }
  //Add an additional 2 "-" for the borders of the map
  os << "-" << "-" << std::endl;

  for (auto const &i : space_instance.space_matrix_) {
    //i is a reference to the space_matrix_ vector
    os << "|";
    for (auto const &j : i) {
      //j is the value in the
      if (j == SpaceRepresentation2D::SpaceType::Free) {
        os << " ";
      } else if (j == SpaceRepresentation2D::SpaceType::Occupied) {
        os << "*";
      } else if (j == SpaceRepresentation2D::SpaceType::Unknown){
        os << "=";
      }

      //! check if j is at the end of the current vector.
      if (&j == &i.back()) {
        os << "|";
      }
    }
    os << std::endl;
  }


  /**
   * Print a row of -- at the bottom of the map
   */
  for (auto col : space_instance.space_matrix_[0]) {
    os << "-";
  }
  //Add an additional 2 "-" for the borders of the map
  os << "-" << "-" << std::endl;
  return os;
}
