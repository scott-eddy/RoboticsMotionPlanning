cmake_minimum_required (VERSION 3.8)

find_package(GTest REQUIRED)
enable_testing()

add_executable(space_representation_2d_tests ${CMAKE_CURRENT_LIST_DIR}/space_representation_2d_tests.cpp)
target_link_libraries(space_representation_2d_tests map_lib ${GTEST_LIBRARIES})


add_test(space_representation_2d_tests map_lib_tests)

