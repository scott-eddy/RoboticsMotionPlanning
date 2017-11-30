//
// Created by Eddy Scott on 11/29/17.
//

#ifndef ROBOTICSMOTIONPLANNING_MAP_TOOLS_SPACE_TRANSFORMATIONS_H
#define ROBOTICSMOTIONPLANNING_MAP_TOOLS_SPACE_TRANSFORMATIONS_H

#include "space_representation_2D.h"
#include "map_tools_geometry.h"
namespace map_tools::space_transformations {

/**
 * Returns a rectangle that fully defines the bounding box described by the amount of free space in the x and y directions
 * @param free_space
 * @param position
 * @return
 */
map_tools::geometry::Rectangle GetBoundingBoxFromPoseAndSize(const std::tuple<int, int> &free_space,
                                                             const map_tools::geometry::Point2D &position);

void CombineSpaceRepresentations(const SpaceRepresentation2D &frame_to_transform,
                                 const map_tools::geometry::Pose2D &pose_of_frame,
                                 SpaceRepresentation2D &destination_frame);

map_tools::geometry::Point2D TransformPoint(const map_tools::geometry::Point2D &point_to_transform,
                                            const double orientation,
                                            const map_tools::geometry::Point2D &origin_translation);

} // map_tools::space_transformations

#endif //ROBOTICSMOTIONPLANNING_MAP_TOOLS_SPACE_TRANSFORMATIONS_H
