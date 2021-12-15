cmake_minimum_required(VERSION 2.6)

project(SZE-MOSZE-2020-Bukottak_bosszuja)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable( runTests unittests.cpp ${PARENT_DIR}/myTable.cpp ${PARENT_DIR}/Cell.cpp )
target_link_libraries(runTests gtest gtest_main pthread)
target_compile_features(runTests PRIVATE cxx_std_17)
