#pragma once
#ifndef ROBOTSCREATE_ENVIRONMENT_DESCRIBER_H
#define ROBOTSCREATE_ENVIRONMENT_DESCRIBER_H

#include "robot.h"
#include "Map_Object.h"
#include "Obstacle.h"
#include "Interest_Point.h"
#include "Robot_Commander.h"
#include "Robot_Scout.h"
#include "Observation_Center.h"
#include "Module.h"

namespace robo {
    /*struct coordinates {
        unsigned int x;
        unsigned int y;
    };

    enum Characters {
        Obstacle_t,
        Interest_t,
        Command_Center_t,
        Robot_Commander_t,
        Observation_Center_t,
        Robot_Scout_t
    };*/

    class Environment_describer {
    private:
        unsigned int width;
        unsigned int height;
        unsigned int time;
        std::vector<Map_Object *> map_obj;

        /// @param bool coord : x - true, y - false
        int setWidthHeight(int, bool);

    public:
        Environment_describer() : time(0), width(0), height(0) {
            //Map_Object::setEnv(this);
        };

        Environment_describer(int, int);

        void setWidth(unsigned int nval) { setWidthHeight(nval, true); }

        void setHeight(unsigned nval) { setWidthHeight(nval, false); }

        unsigned int getWidth() { return width; };

        unsigned int getHeight() { return height; };

        coordinates getObject(Map_Object &);

        Map_Object *getObject(coordinates);

        Map_Object *setObject(Characters, coordinates);

        Map_Object *setObject(Characters, unsigned int, unsigned int, int, std::vector<Module *> &, std::string &, coordinates);

        Map_Object *setObject(Characters, unsigned int, unsigned int, int, std::vector<Module *> &, std::string &,
                              unsigned int);

//        Quick_Navigator qTree;

        void print(std::ostream &stream = std::cout);

        ~Environment_describer() = default; // clear vector
    };
}

#endif //ROBOTSCREATE_ENVIRONMENT_DESCRIBER_H
