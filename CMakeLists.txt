#This defines the build process for the Robotics Motion Planning package
cmake_minimum_required (VERSION 3.8)
project (RoboticsMotionPlanning)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(map_tools
		${CMAKE_CURRENT_LIST_DIR}/src/OccupancyGridBuilding/map_tools_space_transformations.cpp)
target_include_directories(map_tools
		BEFORE
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(map_lib ${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/map.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/rectangle_room.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/map_tools_geometry_line.cpp
        			${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/space_representation_2D.cpp
					)
target_include_directories(map_lib
        BEFORE
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(map_lib map_tools)

add_executable(map_generation ${CMAKE_CURRENT_SOURCE_DIR}/src/map_generation.cpp)

target_link_libraries(map_generation map_lib)

option(BUILD_TESTS "Will build unit tests if set to ON" ON)
if(BUILD_TESTS)
	include(${CMAKE_CURRENT_SOURCE_DIR}/test/MapGenerationTests.cmake)
endif()