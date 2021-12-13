cmake_minimum_required(VERSION 2.8...3.13)

project(MOSZE2021)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
add_executable( runTests unittests.cpp )
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
target_compile_features(runTests PRIVATE cxx_std_17)
