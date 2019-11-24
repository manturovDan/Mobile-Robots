cmake_minimum_required(VERSION 3.15)
project(robotsCreate)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "~/source/libraries/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "~/source/libraries/SFML-2.5.1/lib")
set(SFML_DIR "~/source/libraries/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(robotsCreate main.cpp robots/robot.h robots/environment.cpp robots/interface.h robots/interface.cpp libraries/tinyxml2-lib/tinyxml2.h libraries/tinyxml2-lib/tinyxml2.cpp)

target_link_libraries(robotsCreate sfml-graphics sfml-window sfml-audio)