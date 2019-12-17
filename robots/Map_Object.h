#ifndef ROBOTSCREATE_MAP_OBJECT_H
#define ROBOTSCREATE_MAP_OBJECT_H

#include <iostream>
#include <string>
#include <sstream>

#include "robot.h"

namespace robo {
    class Environment_describer;
    /**
     * Abstract class of any object thr Environment
     **/
    class Map_Object {
    protected:
        bool appeared; /** true if object is static or appeared mobile */
        coordinates position; /** position in the tiled environment map*/
        static Environment_describer * env; /** static field of Environment describer when objects state */
    public:
        /**
         * constructor for mobile robots
         * */
        Map_Object() : appeared(false), position({0, 0}) {}


        /**
         * constructor for static robots where start position never changes
         * and defined in the beginning of the program
         */
        explicit Map_Object(coordinates coords);


        /**
         * getter @returns X coordinate of object in current time
         * (position.x)
         * */
        unsigned int getX() const { return position.x; }


        /**
         * getter @returns Y coordinate of object in current time
         * (position.y)
         * */
        unsigned int getY() const { return position.y; }


        /**
         * static method to assign \env
         * @envd - pointer to connecting Environment describer object
         * */
        static void setEnv(Environment_describer *envd);


        /**
         * getter of position
         * @return value /position
         */
        coordinates getPosition() const { return position; }


        /**
         * the binary operator of equation
         * @left, @right - operands
         * @return true [false] is x- and y- coordinates of an object are equal
         * */
        friend bool operator==(const Map_Object &left, const Map_Object &right) {
            return ((left.position.x == right.position.x) && (left.position.y == right.position.y));
        }


        /**
         * debug method prints position of and object that returns in the flow
         * the Map_Object position
         * @s - stream (definitely std::cout)
         */
        void print(std::ostream & s = std::cout) const { s << position.x << " " << position.y << std::endl; }


        /**
         * abstract method for debug thar returns the string of object information
         * also uses in tests
         * */
        virtual std::string whoami() = 0;


        /**
         * getter of @appeared field
         * */
        bool isAppeared() const { return appeared; }


        /**
         *virtual constructor because there are derived classes
         */
        virtual ~Map_Object() = default;
    };
}

#endif //ROBOTSCREATE_MAP_OBJECT_H
