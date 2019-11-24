#include <iostream>
#include <algorithm>

#include "robot.h"

namespace robo {
    Environment_describer::Environment_describer(int widthG, int heightG) : Environment_describer() {
        if (widthG > 1000 || widthG < 10 || height > heightG || heightG < 10)
            throw std::invalid_argument("Incorrect map params!");
        width = widthG;
        height = heightG;
    }

    int Environment_describer::setWidthHeight(int newVal, bool coord) {
        if (newVal > 1000 || newVal < 10)
            throw std::invalid_argument("Incorrect map params!");
        if (coord)
            width = newVal;
        else
            height = newVal;

        auto map_resident = map_obj.begin();
        /*while (map_resident != map_obj.end()) {
            if ((map_resident->getX() <= newVal && coord) || ((*map_resident)->getY() <= newVal && coord)) { //delete this
                th
            }

            ++map_resident;
        }*/

        //map_obj.erase(std::remove(map_obj.begin(), map_obj.end(), nullptr), map_obj.end()); // or error
        //TODO Dont forget about robots

        return 0;
    }


    Map_Object * Environment_describer::setObject(robo::coordinates position, Characters objType, std::string description) {
        if (position.x >= width || position.y >= height)
            throw std::invalid_argument("Incorrect object coordinates!");
        Map_Object * nw_obj = nullptr;
        if (objType == Obstacle_t) {
            nw_obj = new Obstacle(position);
        } else if (objType == Interest_t) {
            nw_obj = new Interest_Point(position);
        }

        //map_obj.push_back(nw_obj);//copy and delete???
        return nw_obj;
    }


    Map_Object::Map_Object(robo::coordinates pos) {
        position = pos;
        //Continue
    }

    bool operator<(const Map_Object &left, const Map_Object &right){
        if (left.position.x < right.position.x)
            return true;
        else if(left.position.x == right.position.x)
            return left.position.y < right.position.y;
        else
            return false;
    }

    Map_Object * QuickNavigator::check(coordinates position) {
        robo::Map_Object justObj(position);

    }
}
