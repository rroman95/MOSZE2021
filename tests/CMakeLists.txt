cmake_minimum_required(VERSION 2.6)

project(SZE-MOSZE-2021-Successfully_Failed)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable( runUnitTest unit_tests.cpp ${PARENT_DIR}/myTable.cpp ${PARENT_DIR}/Cell.cpp ${PARENT_DIR}/CommandParsing.cpp ${PARENT_DIR}/fileParsing.cpp)
target_link_libraries(runUnitTest gtest gtest_main pthread)
target_compile_features(runUnitTest PRIVATE cxx_std_17)
