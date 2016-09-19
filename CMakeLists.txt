#This defines the build process for the Robotics Motion Planning package

cmake_minimum_required (VERSION 2.6)
project (RoboticsMotionPlanning)

#Add the "include" directory to the project
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(map_lib ${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/map.cpp)

add_executable(map_generation ${CMAKE_CURRENT_SOURCE_DIR}/src/map_generation.cpp)

target_link_libraries(map_generation map_lib)