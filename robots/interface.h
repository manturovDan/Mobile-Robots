#ifndef ROBOTS_INTERFACE_H
#define ROBOTS_INTERFACE_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "../libraries/tinyxml2-lib/tinyxml2.h"
#include <typeinfo>

#include "Environment_describer.h"
#include "Map_Object.h"
#include "Robot_Commander.h"
#include "Power_Generator.h"
#include "Sensor.h"
#include "Managing.h"

namespace interf {
    /// Class that creates Environment from XML FILE
    class EnvXMLCreate {
    public:
        /**
         * default constructor is deleted
         * */
        EnvXMLCreate() = delete;

        /**
         * @filename std::string path - path of XML file
         * @env - empty environment that we create
         * @stream - flow - where we print information
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
         *                                          consumption = ROBOT_CONSUMPTION
         *          these objects may have child elements - modules (not more than PORTS_COUNT)
         *
         *          [not now, maybe later ]Objects (mobile robots) 4,6 must have attribute speed=SPEED
         *
         *          All objects besides 3,6 MUST have attributes x and y with X_POS, Y_POS in half-interval [0, width/height of Environment)
         *
         *              a)
         *              <Power_Generator production = NUM_PRODUCTION priority = PRIORITY />
         *              b)
         *              <Managing consumption = NUM_CONSUMPTION radius = RADIUS_OF_THE_POWER  priority = PRIORITY />
         *              c)
         *              <Sensor consumption = NUM_CONSUMPTION radius = NUM_RADIUS direction = NUM_DIRECTION angle = ANGLE priority = PRIORITY />
         *
         *              direction is not required if angle is 2 (260 deg)
         *
         *          NUM_DIRECTION as Mobile-class field "direction" must be one of 0 (top), 1 (left), 2 (bottom), 3(right)
         *
         *          ANGLE is in 0-2
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
         *          2:
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
         *          Objects 3-4 MUST have one or more Managing module (PORTS_COUNT > 0) and subordinates_count = SUBORDINATES_COUNT param
         *
         *          At the beginning generators and managing modules are active, sensors are inactive
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
         *     <Robot_Commander description = "R2D2" pots = "10" consumption = "5">
         *          <Power_Generator production = "25">
         *          <Managing consumption = "12" power = "8">
         *          <Sensor consumption = "4" direction = "1" angle = "2">
         *          <Sensor consumption = "8" direction = "3" angle = "1">
         *     </Robot_Commander>
         * </Environment>
         */

        EnvXMLCreate(const std::string &, robo::Environment_describer &, std::ostream & stream = std::cout);

    private:
        /**
         * common method that calls when something with file is wrong
         * */
        static void fileDamaged(std::ostream &, const std::string & add = "unknown");
    };

    /**
     * class to stay SOLID concept - prints all environment
     * and input from cin
     * */
    class InterfaceTools {
    private:
        robo::Environment_describer * env;
    public:
        InterfaceTools(robo::Environment_describer * ev) { env = ev; }
        void printEnv(std::ostream & stream = std::cout);
    };
}

#endif //ROBOTS_INTERFACE_H
