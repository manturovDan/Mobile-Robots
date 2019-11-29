#ifndef ROBOTSCREATE_MAP_OBJECT_H
#define ROBOTSCREATE_MAP_OBJECT_H

#include <iostream>

#include "robot.h"

namespace robo {
    class Map_Object {
    protected:
        bool appeared;
        coordinates position;
        static Environment_describer *env;
    public:
        Map_Object(coordinates);

        Map_Object() : appeared(false), position({0, 0}) {}

        static void setEnv(Environment_describer *envir) { env = envir; }

        unsigned int getX() { return position.x; }

        unsigned int getY() { return position.y; }

        coordinates getPosition() { return position; }

        friend bool operator<(const Map_Object &, const Map_Object &);

        friend bool operator==(const Map_Object &left, const Map_Object &right) {
            return ((left.position.x == right.position.x) && (left.position.y == right.position.y));
        }

        void print() { std::cout << position.x << " " << position.y << std::endl; }

        //virtual Map_Object * clone() const = 0; //НУЖНО ЛИ??? ASK

    };
}

#endif //ROBOTSCREATE_MAP_OBJECT_H
