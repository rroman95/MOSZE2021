cmake_minimum_required(VERSION 2.6)

project(MOSZE2021)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

add_executable( runTests unitests.cpp ${PARENT_DIR}/myTable.cpp ${PARENT_DIR}/Cell.cpp ${PARENT_DIR}/CommandParsing.cpp ${PARENT_DIR}/fileParsing.cpp )
target_link_libraries(runTests gtest gtest_main pthread)
target_compile_features(runTests PRIVATE cxx_std_17)
