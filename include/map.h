/**
 * This is a class that defines a map.  A map is composed of 
 * free space and occupied space a-la an occupancy grid
 *
*/

#pragma once
#include <vector>
#include <iostream>
#include "map_tools_geometry.h"
#include "room.h"
#include "rectangle_room.h"
#include "space_representation_2D.h"


class Map {
 public:
  /**
   * @brief Default constructor
   * @details makes a map of default size [30x30]
   */
  Map();

  /**
   * @brief Constructor of th map
   * @details Generates the matrix of free and occupied space
   *
   * @param max_space_x the maximum size of the map in the x direction
   * @param max_space_y the maximum size of the map in the y direction
   */
  Map(int max_space_x, int max_space_y);

  /**
   * @brief Destructor of map
   */
  ~Map() = default;

  //! Represent a matrix as a vector of vectors.
  //! Could be done with template matrix class ala Eigen
  SpaceRepresentation2D space_matrix_;

  /**
   * @brief Prints the map as ASCII
   * @details Prints a representation of the map with free space
   *          printed as " " and occupied space printed with "*"
   *          The map is bordered with "-" at top and bottom and "|"
   *          on either side
   *
   * @param os ostream to be printed to
   * @param map_instance map object to be printed out
   */
  friend std::ostream &operator<<(std::ostream &os, const Map &map_instance);

  /**
   * \brief Generates a pointer to a room containing the requested free space with the given origin
   * @param free_space: The amount of free space (size) the room can occupy in the x and y directions
   * @param pose: The origin of the room in the Map coordinate frame as well as the orientation with respect to the map frame
   */
  void AddRoom(std::tuple<int, int> free_space, map_tools::geometry::Pose2D pose);

  /**
   * @brief Populates a map with rooms and passageways
   * TODO [issue #3] move this functionality to a factory class
   */
  void GenerateMap();
 private:

  /**
   * \brief the size of the room in the X direction when the default Ctor is called
   */
  static constexpr size_t default_map_size_x_ = 30;

  /**
   * \brief the size of the room in the Y direction when the default Ctor is called
   */
  static constexpr size_t default_map_size_y_ = 30;

  /**
   * \brief limits the max size of any room in the map.  The scale factor limits max_room_size(x/y) to be <= to
   * room_max_size_scale_factor * size_(x/y)_
   *
   * For example, a scale factor of 0.2 will limit the x/y max size of any room to be 20% of the size of the entire map
   */
  static constexpr double room_max_size_scale_factor_ = 0.2;

  /**
   * \brief size of the map in the x direction, origin top left indexed from 0
   */
  int size_x_;

  /**
   * \brief size of the map in the y direction, origin top left indexed from 0
   */
  int size_y_;

  /**
   * \brief max size of any room in the X direction
   */
  int max_room_size_x_;

  /**
   * \brief max size of any room in the Y direction
   */
  int max_room_size_y_;

  /**
   * \brief vector of rooms making up this map
   */
  std::vector<std::unique_ptr<Room>> room_vector_;

  /**
   * @brief returns true if two rooms in the map intersect one another
   */
  bool BoundingBoxIntersection(const map_tools::geometry::Rectangle &new_bounding_box);

  /**
   *
   * @return true if upperleft and lowerright of potential Room is capped to [(0,0), (sizeX, sizeY)]
   */
  bool BoundingBoxWithinMap(const map_tools::geometry::Rectangle &new_bounding_box);
};
