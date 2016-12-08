#This defines the build process for the Robotics Motion Planning package
cmake_minimum_required (VERSION 2.6)
project (RoboticsMotionPlanning)

#-------------------------------------------------------------------#
#First ensure that we compile against c++11 features as the whole
#point of this project is really to get aquanted with modern c++
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	message(STATUS "C++11 support found")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	message(STATUS "C++0x support found")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
#------------------------------------------------------------------#
# Build the mapping toolkit library
# Add the "include" directory to the project
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/MapToolkit)

add_library(map_lib ${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/map.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/rectangle_room.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/line.cpp
                                        ${CMAKE_CURRENT_SOURCE_DIR}/src/OccupancyGridBuilding/VectorSpaceRepresentation.cpp)
add_executable(map_generation ${CMAKE_CURRENT_SOURCE_DIR}/src/map_generation.cpp)

target_link_libraries(map_generation map_lib)
#------------------------------------------------------------------#
# For better visualization of data build the animation toolkit library
set(MAKE_ANIMATION FALSE)

if(MAKE_ANIMATION)
    find_package(OpenCV REQUIRED)
    
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/AnimationToolkit)
    add_executable(opencvTest ${CMAKE_CURRENT_SOURCE_DIR}/src/AnimationToolkit/opencvDemo.cpp)
    target_link_libraries( opencvTest ${OpenCV_LIBS} )

endif()

