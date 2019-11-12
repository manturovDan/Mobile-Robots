#include <iostream>

#include "robot.h"

namespace robo {
    Environment_describer::Environment_describer(int width, int height) {
        if (width > 1000 || width < 10 || height > 1000 || height < 10)
            throw std::invalid_argument("Incorrect map params!");
    }

    Map_Object * Environment_describer::setObject(robo::map_position position, std::string objType, std::string description) {
        if (position.x < 0 || position.x >= width || position.y < 0 || position.y >= height)
            throw std::invalid_argument("Incorrect object coordinates!");
        Map_Object * nw_obj = nullptr;
        if (objType == "Obstacle") {
            nw_obj = new Obstacle(position);
        } else if (objType == "Interest_Point") {
            nw_obj = new Interest_Point(position);
        }

        map_obj.push_back(nw_obj);
        return nw_obj;
    }

    Map_Object::Map_Object(robo::map_position pos) {
        if (pos.x < 0 || pos.y < 0)
            throw std::invalid_argument("Incorrect object coordinates!");

        position.x = pos.x;
    }
}
