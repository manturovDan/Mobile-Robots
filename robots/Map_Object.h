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
        Environment_describer * env;
    public:
        Map_Object() : appeared(false), position({0, 0}) {}

        Map_Object(coordinates coords) : appeared(true), position(coords) {} //TODO Normal

        unsigned int getX() { return position.x; }

        unsigned int getY() { return position.y; }

        coordinates getPosition() { return position; }

        int testEnv();

        //friend bool operator<(const Map_Object &, const Map_Object &);

        friend bool operator==(const Map_Object &left, const Map_Object &right) {
            return ((left.position.x == right.position.x) && (left.position.y == right.position.y));
        }

        void print() { std::cout << position.x << " " << position.y << std::endl; }

        virtual std::string whoami() = 0;
        //virtual Map_Object * clone() const = 0; //НУЖНО ЛИ??? ASK

        virtual ~Map_Object() = default;
    };
}

#endif //ROBOTSCREATE_MAP_OBJECT_H
