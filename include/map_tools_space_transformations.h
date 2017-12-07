//
// Created by Eddy Scott on 11/29/17.
//

#ifndef ROBOTICSMOTIONPLANNING_MAP_TOOLS_SPACE_TRANSFORMATIONS_H
#define ROBOTICSMOTIONPLANNING_MAP_TOOLS_SPACE_TRANSFORMATIONS_H

#include "space_representation_2D.h"
#include "map_tools_geometry.h"
namespace map_tools::space_transformations {


/**
 *
 * @param point_to_transform
 * @param orientation
 * @param origin_translation
 * @return
 */
// TODO 12/2017 what about other types of translation
map_tools::geometry::Point2D TransformPoint(const map_tools::geometry::Point2D &point_to_transform,
                                            double orientation,
                                            const map_tools::geometry::Point2D &origin_translation);

/**
 * Returns a rectangle that fully defines the bounding box described by the amount of free space in the x and y directions
 * and the
 * @param free_space
 * @param origin_pose
 * @return
 */
map_tools::geometry::Rectangle GetBoundingBoxFromPoseAndSize(const std::tuple<int, int> &free_space,
                                                             const geometry::Pose2D &origin_pose);

void CombineSpaceRepresentations(const SpaceRepresentation2D &frame_to_transform,
                                 const map_tools::geometry::Pose2D &pose_of_frame,
                                 SpaceRepresentation2D &destination_frame);

} // map_tools::space_transformations

#endif //ROBOTICSMOTIONPLANNING_MAP_TOOLS_SPACE_TRANSFORMATIONS_H
