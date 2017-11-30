//
// Created by Eddy Scott on 11/26/17.
//

#include <gtest/gtest.h>
#include "space_representation_2D.h"

/**
 * Ensures that the function operator can be used to both assign values and to access values
 */
TEST(SpaceRepresenation2dTesting, ASCIIPrintingWorks){
  // Arrange
  SpaceRepresentation2D matrix_under_test(3,1);

  matrix_under_test(0,0) = SpaceRepresentation2D::SpaceType::Unknown;
  matrix_under_test(1,0) = SpaceRepresentation2D::SpaceType::Free;
  matrix_under_test(2,0) = SpaceRepresentation2D::SpaceType::Occupied;

  std::cout << matrix_under_test << std::endl;
}

/**
 * Ensures that the function operator can be used to both assign values and to access values
 */
TEST(SpaceRepresenation2dTesting, FunctionOperatorOverload){
  // Arrange
  SpaceRepresentation2D matrix_under_test(1,1);

  // Act
  matrix_under_test(0,0) = SpaceRepresentation2D::SpaceType::Occupied;

  // Assert
  ASSERT_EQ(SpaceRepresentation2D::SpaceType::Occupied, matrix_under_test(0,0));
}

/**
 * Ensures that the SpaceRepresentation initializes all underlying data to SpaceType::Unkown
 */
TEST(SpaceRepresenation2dTesting, DefulatInitialization){
  // Arrange
  SpaceRepresentation2D matrix_under_test(10,10);

  // Act,Assert
  for(auto const& row : matrix_under_test.GetSpaceAsMatrix()){
    for(auto const& value : row){
      ASSERT_EQ(SpaceRepresentation2D::SpaceType::Unknown, value);
    }
  }
}


int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);

  int ret = RUN_ALL_TESTS();
  return ret;
}
