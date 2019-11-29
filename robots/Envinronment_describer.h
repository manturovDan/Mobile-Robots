#ifndef ROBOTSCREATE_ENVINRONMENT_DESCRIBER_H
#define ROBOTSCREATE_ENVINRONMENT_DESCRIBER_H

#include "robot.h"
#include "Map_Object.h"

namespace robo {
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
            Map_Object::setEnv(this);
        };

        Environment_describer(int, int);

        void setWidth(unsigned int nval) { setWidthHeight(nval, true); }

        void setHeight(unsigned nval) { setWidthHeight(nval, false); }

        unsigned int getWidth() { return width; };

        unsigned int getHeight() { return height; };

        coordinates getObject(Map_Object &);

        Map_Object *getObject(coordinates);

        Map_Object *setObject(coordinates, Characters);

        Map_Object *setObject(unsigned int, unsigned int, int, std::vector<Module *> &, Characters, std::string &);

        Map_Object *
        setObject(coordinates, unsigned int, unsigned int, int, std::vector<Module *> &, Characters, std::string &);

        Quick_Navigator qTree;

        void print(std::ostream &stream = std::cout);

        ~Environment_describer() = default; // clear vector
    };
}

#endif //ROBOTSCREATE_ENVINRONMENT_DESCRIBER_H
