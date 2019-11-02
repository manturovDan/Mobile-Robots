cmake_minimum_required(VERSION 3.15)
project(diagram)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(diagram src/main.cpp src/diagram.h src/diagram.cpp src/diagfile.h src/diagfile.cpp tinyxml2-lib/tinyxml2.h tinyxml2-lib/tinyxml2.cpp)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(u_test src/test.cpp src/diagram.cpp src/diagram.h)
target_link_libraries(u_test ${GTEST_LIBRARIES} pthread)
add_test(NAME uTest COMMAND u_test)