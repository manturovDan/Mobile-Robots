cmake_minimum_required(VERSION 3.15)
project(multisetTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(multisetTest main.cpp multiset.h)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(u_test test.cpp multiset.h)
target_link_libraries(u_test ${GTEST_LIBRARIES} pthread)
add_test(NAME uTest COMMAND u_test)

