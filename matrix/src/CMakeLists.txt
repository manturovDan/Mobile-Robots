cmake_minimum_required(VERSION 3.2)
project(matrix_pr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(exem main.cpp matrixr.cpp matrixr.h)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(u_test test.cpp matrixr.cpp matrixr.h)
target_link_libraries(u_test ${GTEST_LIBRARIES} pthread)

add_test(NAME uTest COMMAND u_test)
