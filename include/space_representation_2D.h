
#ifndef ROBOTICSMOTIONPLANNING_SPACEREPRESENTATION2D_H
#define ROBOTICSMOTIONPLANNING_SPACEREPRESENTATION2D_H

#include <vector>

/**
 * \brief Class that abstracts how space is represented in two dimensions.  Currently this is done by storing a vector
 *        of vectors to generate a 2D matrix. The matrix is then filled with different data depending on what the
 *        underlying space is
 *
 * \details
 * ```
 * |(0,0) | (1,0) | (2,0) |
 * |(0,1) | (1,1) | (2,1) |
 * ```
 *
 */
class SpaceRepresentation2D {
 public:

  enum class SpaceType {
    Unknown = -1,
    Free = 0,
    Occupied = 1
  };


  SpaceRepresentation2D(int size_x_dir, int size_y_dir);

  ~SpaceRepresentation2D() = default;

  /**
   * Allow assignment of an element in the space matrix by returning a reference to the element
   * @param row: The column within the matrix to access
   * @param column: The column within the matrix to access
   * @return The SpaceType value of the element located at row, column
   */
  SpaceType& operator()(size_t row, size_t column);

  /**
   * Allow accessing a const reference of an element in the space matrix
   * @param row: The column within the matrix to access
   * @param column: The column within the matrix to access
   * @return The SpaceType value of the element located at row, column
   */
  const SpaceType& operator()(size_t row, size_t column) const;

 private:
  std::vector<std::vector<SpaceType>> space_matrix_;


};

#endif //ROBOTICSMOTIONPLANNING_SPACEREPRESENTATION2D_H
