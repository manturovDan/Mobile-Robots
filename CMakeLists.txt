cmake_minimum_required(VERSION 3.15)
project(robotsCreate)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "~/source/libraries/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "~/source/libraries/SFML-2.5.1/lib")
set(SFML_DIR "~/source/libraries/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_library(interfacelib robots/interface.h robots/interface.cpp)
add_library(obstacle robots/Obstacle.h robots/Obstacle.cpp)
add_library(tinyxml2 libraries/tinyxml2-lib/tinyxml2.h libraries/tinyxml2-lib/tinyxml2.cpp)
add_library(map_object robots/Map_Object.h robots/Map_Object.cpp)
add_library(environment_describer robots/Environment_describer.h robots/Environment_describer.cpp)
add_library(interest_point robots/Interest_Point.h robots/Interest_Point.cpp)
add_library(observation_center robots/Observation_Center.h robots/Observation_Center.cpp)
add_library(command_center robots/Command_Center.h robots/Command_Center.cpp)
add_library(robot_scout robots/Robot_Scout.h robots/Robot_Scout.cpp)
add_library(robot_commander robots/Robot_Commander.h robots/Robot_Commander.cpp)
add_library(module robots/Module.h robots/Module.cpp)
add_library(power_generator robots/Power_Generator.h robots/Power_Generator.cpp)
add_library(managing robots/Managing.h robots/Managing.cpp)
add_library(sensor robots/Sensor.h robots/Sensor.cpp)
add_library(display robots/Display.h robots/Display.cpp)
add_library(moving_describer robots/Moving_Describer.h robots/Moving_Describer.cpp)
add_library(ai_robots robots/Ai_Deep.h robots/Ai_Deep.cpp)

target_link_libraries(obstacle map_object)
target_link_libraries(environment_describer map_object obstacle)
target_link_libraries(map_object environment_describer)
target_link_libraries(sensor environment_describer)
target_link_libraries(observation_center sensor)

add_executable(robotsCreate main.cpp robots/robot.h)

target_link_libraries(robotsCreate interfacelib obstacle tinyxml2 map_object environment_describer interest_point
        observation_center command_center robot_scout robot_commander module power_generator managing sensor display
        moving_describer ai_robots)

target_link_libraries(robotsCreate sfml-graphics sfml-window sfml-audio)