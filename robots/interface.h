#ifndef ROBOTS_INTERFACE_H
#define ROBOTS_INTERFACE_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "../libraries/tinyxml2-lib/tinyxml2.h"

#include "robot.h"

namespace interf {
    /// Class that creates Environment from XML FILE
    class EnvXMLCreate {
    public:
        EnvXMLCreate() = delete;

        ///@param std::string path - path of XML file
        /**
         * format of XML file:
         * <Environment width = WIDTH_OF_MAP height = HEIGHT_OF_MAP>
         *      <OBJECT_TYPE ...>
         *          ...
         *      </OBJECT_TYPE>
         *      or
         *      <OBJECT_TYPE ... />
         *
         *          OBJECT_TYPE must be the one of the following:
         *          1) Obstacle
         *          2) Interest
         *          3) Command_Center
         *          4) Robot_Commander
         *          5) Observation_Center
         *          6) Robot_Scout
         *
         *          Objects 3-6 must have attribute description = DESC (max 256 symbols),
         *                                          ports = PORTS_COUNT,
         *          these objects may have child elements - modules (not more than PORTS_COUNT)
         *
         *          All objects besides 3,6 MUST have attributes x and y with X_POS, Y_POS in half-interval [0, width/height of Environment)
         *
         *              a)
         *              <Power_Generator production = NUM_PRODUCTION />
         *              b)
         *              <Managing consumption = NUM_CONSUMPTION radius = RADIUS_OF_THE_POWER /  >
         *              c)
         *              <Sensor consumption = NUM_CONSUMPTION radius = NUM_RADIUS direction = NUM_DIRECTION angle = ANGLE>
         *
         *          NUM_DIRECTION as Mobile-class field "direction" must be one of 0 (top), 1 (left), 2 (bottom), 3(right)
         *
         *          ANGLE is in 0-4
         *          Types of angles on examples with radius = "4"   # - robot, x - in vision, o - out vision
         *          0:
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          oooo#oooo
         *          ooooooooo
         *          ooooooooo
         *          ooooooooo
         *          ooooooooo
         *
         *          1:
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxx#oooo
         *          xxxxooooo
         *          xxxxooooo
         *          xxxxooooo
         *          xxxxooooo
         *
         *          3:
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          oooo#xxxx
         *          ooooxxxxx
         *          ooooxxxxx
         *          ooooxxxxx
         *          ooooxxxxx
         *
         *          4:
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxx#xxxx
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxxxxxxx
         *          xxxxxxxxx
         *
         *          Objects 3-4 MUST have one or more Managing module (PORTS_COUNT > 0)
         *
         * </Environment>
         *
         * Excample:
         * <Environment width = "100" height = "250">
         *     <Obstacle x = "1" y = "1"/>
         *     <Obstacle x = "1" y = "2"/>
         *     <Obstacle x = "50" y = "20"/>
         *
         *     <Interest x = "50" y = "22"/>
         *     <Interest x = "10" y = "14"/>
         *
         *     <Robot_Commander description = "R2D2" pots = 10>
         *          <Power_Generator production = "25">
         *          <Managing consumption = "12" power = "8">
         *          <Sensor consumption = "4" direction = "1" angle = "2">
         *          <Sensor consumption = "8" direction = "3" angle = "1">
         *     </Robot_Commander>
         * </Environment>
         */


        EnvXMLCreate(const std::string &, robo::Environment_describer &, std::ostream & stream = std::cout);

    private:
        static void fileDamaged(std::ostream &, const std::string & add = "unknown");
    };
}

#endif //ROBOTS_INTERFACE_H
