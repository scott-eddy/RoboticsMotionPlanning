//
// Created by Eddy Scott on 11/29/17.
//

#include <cmath>
#include "map_tools_space_transformations.h"

map_tools::geometry::Point2D map_tools::space_transformations::TransformPoint(const map_tools::geometry::Point2D &point_to_transform,
                                            double orientation,
                                            const map_tools::geometry::Point2D &origin_translation){
  /**
   * Room is rotated by \theta radians of rotation and then the origin is translated by origin_translation in the x/y
   * Therefore we perform:
   * x_new = x*cos(\theta) - y*sin(\theta) + x_translation
   * y_new = x*sin(\theta) + y*cos(\theta) + y_translation
   */
  map_tools::geometry::Point2D transformed_point;
  transformed_point.x = static_cast<int>(point_to_transform.x * std::cos(orientation) - point_to_transform.y * std::sin(orientation) + origin_translation.x);
  transformed_point.y = static_cast<int>(point_to_transform.x * std::sin(orientation) + point_to_transform.y * std::cos(orientation) + origin_translation.y);
  return transformed_point;
}

map_tools::geometry::Rectangle map_tools::space_transformations::GetBoundingBoxFromPoseAndSize(const std::tuple<int,
                                                                                                                int> &free_space,
                                                                                               const geometry::Pose2D &origin_pose) {


  // TODO nomenclature is difficult here, because if the rotation is large or negative the cardinal directions of
  // left/right no longer hold true
  map_tools::geometry::Rectangle boundingBox;

  // The origin of the bounding box (top left point) remains the same as the pose because the
  // origin is rotation independent
  boundingBox.top_left.x = origin_pose.location.x;
  boundingBox.top_left.y = origin_pose.location.y;


  boundingBox.bottom_right.x = origin_pose.location.x + std::get<0>(free_space) / 2;
  boundingBox.bottom_right.y = origin_pose.location.y + std::get<1>(free_space) / 2;
  boundingBox.bottom_right = map_tools::space_transformations::TransformPoint(boundingBox.bottom_right, origin_pose.orientation, origin_pose.location);

  return boundingBox;
}

void map_tools::space_transformations::CombineSpaceRepresentations(const SpaceRepresentation2D &frame_to_transform,
                                                                   const map_tools::geometry::Pose2D &pose_of_frame,
                                                                   SpaceRepresentation2D &destination_frame) {
  std::tuple<int, int> max_size_orig(frame_to_transform.GetSizeX(), frame_to_transform.GetSizeY());
  map_tools::geometry::Rectangle
      bounding_box_orig = map_tools::space_transformations::GetBoundingBoxFromPoseAndSize(max_size_orig, pose_of_frame);

  std::vector<std::pair<map_tools::geometry::Point2D, SpaceRepresentation2D::SpaceType>> points_in_space;

  map_tools::geometry::Point2D point_in_source_frame;
  map_tools::geometry::Point2D point_in_destination_frame;
  for (auto row : frame_to_transform.GetSpaceAsMatrix()) {
    for (auto column : row) {

    }
  }

}

