#ifndef ROBOTSCREATE_MAP_OBJECT_H
#define ROBOTSCREATE_MAP_OBJECT_H

#include <iostream>
#include <string>
#include <sstream>

#include "robot.h"

namespace robo {
    class Environment_describer;
    class Map_Object {
    protected:
        bool appeared;
        coordinates position;
        static Environment_describer * env;
    public:
        Map_Object() : appeared(false), position({0, 0}) {}
        explicit Map_Object(coordinates coords);

        unsigned int getX() const { return position.x; }
        unsigned int getY() const { return position.y; }
        static void setEnv(Environment_describer *envd);
        coordinates getPosition() const { return position; }
        friend bool operator==(const Map_Object &left, const Map_Object &right) {
            return ((left.position.x == right.position.x) && (left.position.y == right.position.y));
        }
        void print() const { std::cout << position.x << " " << position.y << std::endl; }
        virtual std::string whoami() = 0;
        virtual ~Map_Object() = default;
    };
}

#endif //ROBOTSCREATE_MAP_OBJECT_H
