
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

  /**
   * \brief Constructs a 2d matrix with max size: size_x_dir, size_y_dir
   * @param size_x_dir: the size of the space in the x direction
   * @param size_y_dir: the size of the space in the y direction
   * \details NOTE: since the space is held in a 2D matrix the x direction corresponds to the number of columns and
   *                the y direction corresponds to the number of rows in the matrix
   */
  SpaceRepresentation2D(size_t size_x_dir, size_t size_y_dir);

  /**
   * \brief Constructs a 2d matrix with max size: size_x_dir, size_y_dir
   * @param size_x_dir: the size of the space in the x direction
   * @param size_y_dir: the size of the space in the y direction
   * @param
   * \details NOTE: since the space is held in a 2D matrix the x direction corresponds to the number of columns and
   *                the y direction corresponds to the number of rows in the matrix
   */
  SpaceRepresentation2D(size_t size_x_dir, size_t size_y_dir, SpaceType defualt_space_fill);

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

  /**
   * \brief allows clients to see the underlying space representation as a vector of vectors
   * @return
   */
  const std::vector<std::vector<SpaceType>>& GetSpaceAsMatrix(void) const;

 private:
  std::vector<std::vector<SpaceType>> space_matrix_;


};

#endif //ROBOTICSMOTIONPLANNING_SPACEREPRESENTATION2D_H
