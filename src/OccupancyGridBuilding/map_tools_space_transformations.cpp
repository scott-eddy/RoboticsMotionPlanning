//
// Created by Eddy Scott on 11/29/17.
//

#include <map_tools_geometry_line.h>
#include "map_tools_space_transformations.h"

// TODO this should be get new origin from PoseAndSize
map_tools::geometry::Rectangle map_tools::space_transformations::GetBoundingBoxFromPoseAndSize(const std::tuple<int,
                                                                                                                int> &free_space,
                                                                                               const map_tools::geometry::Point2D &position) {

  map_tools::geometry::Rectangle boundingBox;
  boundingBox.top_left.x = position.x - std::get<0>(free_space) / 2;
  boundingBox.top_left.y = position.y - std::get<1>(free_space) / 2;

  boundingBox.bottom_right.x = position.x + std::get<0>(free_space) / 2;
  boundingBox.bottom_right.y = position.y + std::get<1>(free_space) / 2;

  return boundingBox;
}

void map_tools::space_transformations::CombineSpaceRepresentations(const SpaceRepresentation2D &frame_to_transform,
                                                                   const map_tools::geometry::Pose2D &pose_of_frame,
                                                                   SpaceRepresentation2D &destination_frame) {
  std::tuple<int, int> max_size_orig(frame_to_transform.GetSizeX(), frame_to_transform.GetSizeY());
  map_tools::geometry::Rectangle
      bounding_box_orig = GetBoundingBoxFromPoseAndSize(max_size_orig, pose_of_frame.location);

  std::vector<std::pair<map_tools::geometry::Point2D, SpaceRepresentation2D::SpaceType>> points_in_space;

  map_tools::geometry::Point2D point_in_source_frame;
  map_tools::geometry::Point2D point_in_destination_frame;
  for (auto row : frame_to_transform.GetSpaceAsMatrix()) {
    for (auto column : row) {

    }
  }

}

map_tools::geometry::Point2D TransformPoint(const map_tools::geometry::Point2D &point_to_transform,
                                            const double rotation,
                                            const map_tools::geometry::Point2D &origin_translation){
  /**
   * Room is rotated by \theta radians of rotation and then the origin is translated by origin_translation int he x/y
   * Therefore we perform:
   * x_new = x*cos(\theta) - y*sin(\theta) + x_translation
   * y_new = x*sin(\theta) + y*cos(\theta) + y_translation
   *
   */
}
