cmake_minimum_required(VERSION 2.8...3.13)

project(MOSZE2021)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

add_executable( unittests unittests.cpp ${PARENT_DIR}/myTable.cpp ${PARENT_DIR}/Cell.cpp)
target_link_libraries(unittests ${GTEST_LIBRARIES} pthread)
target_compile_features(unittests PRIVATE cxx_std_17)
