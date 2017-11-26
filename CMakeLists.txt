#This defines the build process for the Robotics Motion Planning package
cmake_minimum_required (VERSION 3.8)
project (RoboticsMotionPlanning)

# Require C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add the "include" directory to the project
add_library(map_lib ${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/map.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/rectangle_room.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/line.cpp
        			${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/space_representation_2D.cpp
					)
target_include_directories(map_lib
        BEFORE
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(map_generation ${CMAKE_CURRENT_SOURCE_DIR}/src/map_generation.cpp)

target_link_libraries(map_generation map_lib)