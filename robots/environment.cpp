#include <iostream>
#include <algorithm>

#include "robot.h"

namespace robo {
    Environment_describer::Environment_describer(int widthG, int heightG) {
        if (widthG > 1000 || widthG < 10 || height > heightG || heightG < 10)
            throw std::invalid_argument("Incorrect map params!");
        width = widthG;
        height = heightG;
    }

    int Environment_describer::setWidthHeight(int newVal, bool coord) { //x - true, y - false
        if (newVal > 1000 || newVal < 10)
            throw std::invalid_argument("Incorrect map params!");
        if (coord)
            width = newVal;
        else
            height = newVal;

        auto map_resident = map_obj.begin();
        while (map_resident != map_obj.end()) {
            if (((*map_resident)->getX() <= newVal && coord) || ((*map_resident)->getY() <= newVal && coord)) {
                delete (*map_resident);
                *map_resident = nullptr;
            }

            ++map_resident;
        }

        map_obj.erase(std::remove(map_obj.begin(), map_obj.end(), nullptr), map_obj.end());
        //TODO Dont forget about robots

        return 0;
    }

    Map_Object * Environment_describer::setObject(robo::map_position position, std::string & objType, std::string description) {
        if (position.x < 0 || position.x >= width || position.y < 0 || position.y >= height)
            throw std::invalid_argument("Incorrect object coordinates!");
        Map_Object * nw_obj = nullptr;
        if (objType == "Obstacle") {
            nw_obj = new Obstacle(position);
        } else if (objType == "Interest_Point") {
            nw_obj = new Interest_Point(position);
        }

        map_obj.push_back(nw_obj);//copy and delete???
        return nw_obj;
    }

    Map_Object::Map_Object(robo::map_position pos) {
        if (pos.x < 0 || pos.y < 0)
            throw std::invalid_argument("Incorrect object coordinates!");

        position = pos;
    }
}
