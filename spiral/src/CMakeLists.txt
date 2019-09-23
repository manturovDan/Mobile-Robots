cmake_minimum_required(VERSION 3.2)
project(hello_world_pr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(exem main.cpp hwl.h)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(hello_world_test test.cpp hwl.h)
target_link_libraries(hello_world_test ${GTEST_LIBRARIES} pthread)

add_test(NAME HelloWorldTest COMMAND hello_world_test)
