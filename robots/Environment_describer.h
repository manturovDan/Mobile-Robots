#ifndef ROBOTSCREATE_ENVIRONMENT_DESCRIBER_H
#define ROBOTSCREATE_ENVIRONMENT_DESCRIBER_H

#include "typeinfo"

#include "robot.h"
#include "Map_Object.h"
#include "Obstacle.h"
#include "Interest_Point.h"
#include "Robot_Commander.h"
#include "Robot_Scout.h"
#include "Observation_Center.h"
#include "Module.h"

namespace robo {
    class Env_Consistent_Iter {
    private:
        std::vector<Map_Object *>::iterator iter;
    public:
        Env_Consistent_Iter() = delete;
        Env_Consistent_Iter(std::vector<Map_Object *> & mo) { iter = mo.begin(); }
        Env_Consistent_Iter(std::vector<Map_Object *>::iterator it) { iter = it; }
        Env_Consistent_Iter operator++(int);
        Env_Consistent_Iter & operator++();
        Map_Object * operator*();
        friend bool operator==(Env_Consistent_Iter left, Env_Consistent_Iter right) { return left.iter == right.iter; }
        friend bool operator!=(Env_Consistent_Iter left, Env_Consistent_Iter right) { return left.iter != right.iter; }
    };


    class Environment_describer {
    private:
        unsigned int width;
        unsigned int height;
        unsigned long int time;
        std::vector<Map_Object *> map_obj;

        /// @param bool coord : x - true, y - false
        int setWidthHeight(int, bool);

    public:
        Environment_describer() : time(0), width(0), height(0) { robo::Map_Object::setEnv(this); }
        Environment_describer(int, int);
        void setWidth(unsigned int nval) { setWidthHeight(nval, true); }
        void setHeight(unsigned nval) { setWidthHeight(nval, false); }
        unsigned int getWidth() { return width; };
        unsigned int getHeight() { return height; };
        coordinates getObject(Map_Object &);
        Map_Object *getObject(coordinates);

        Map_Object *setObject(Characters, coordinates);
        Map_Object *setObject(Characters, unsigned int, unsigned int, int, std::vector<Module *> &, std::string &, coordinates);
        Map_Object *setObject(Characters, unsigned int, unsigned int, int, std::vector<Module *> &, std::string &);

        void plusTime() { time++; };
        unsigned int getTime() { return time; }
        void print(std::ostream &stream = std::cout);
        ~Environment_describer() = default; // clear vector
        friend class Env_Consistent_Iter;
        Env_Consistent_Iter begin() { return Env_Consistent_Iter(map_obj); }
        Env_Consistent_Iter end() { return Env_Consistent_Iter(map_obj.end()); }

        std::vector<Map_Object *>::const_iterator ibegin() { return  map_obj.begin(); }
        std::vector<Map_Object *>::const_iterator iend() { return  map_obj.end(); }

        Map_Object * checkStaticPoint(coordinates);
        Map_Object * checkMobOnPoint(coordinates);
    };
}

#endif //ROBOTSCREATE_ENVIRONMENT_DESCRIBER_H
