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
        //Map_Object * is_there = qTree.check(position);

        //if (is_there != nullptr && strcmp(typeid(*is_there).name(), "Interest_Point") != 0)
        //    return nullptr;
        // TODO check free ceil

        Map_Object * nw_obj = nullptr;
        if (objType == Obstacle_t) {
            nw_obj = new Obstacle(position);
        } else if (objType == Interest_t) {
            nw_obj = new Interest_Point(position);
        } else if (objType == Command_Center_t) {
            nw_obj = new Command_Center(position);
        } else if (objType == Robot_Commander_t) {
            nw_obj = new Robot_Commander(position);
        } else if (objType == Observation_Center_t) {
            nw_obj = new Observation_Center(position);
        } else if (objType == Robot_Scout_t) {
            nw_obj = new Robot_Scout(position);
        } else {
            throw std::invalid_argument("Unknown object tries to penetrate in my laboratory work");
        }

        map_obj.push_back(nw_obj); // OR COPY????
        //qTree.add(nw_obj);

        return nw_obj;
    }

    Map_Object * Environment_describer::setObject(unsigned int ports, std::vector<robo::Module *> modules, Characters objType, std::string desc) {
        Map_Object * nw_obj = nullptr;
        if (objType == Robot_Commander_t) {
            nw_obj = new Robot_Commander(position);
        } else if (objType == Robot_Scout_t) {
            nw_obj = new Robot_Scout(position);
        }
    }

    void Environment_describer::print(std::ostream & stream) {
        for (auto & it : map_obj) {
            it->print();
        }
    }

    ///////////////////////////////

    Observation_Center::Observation_Center(coordinates pos, unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods,
            std::string & desc) : Map_Object(pos), description(desc), cost(price), countPorts(ports), energyConsumption(consumption), appeared(true) {

        if (ports < mods.size())
            throw std::invalid_argument("Robot has too many modules");

        for (auto itm : mods) {
            modules.push_back((*itm).copy());
        }

    }

    Map_Object::Map_Object(robo::coordinates pos) : position(pos), appeared(true) {
        //check collision
    }

    void Observation_Center::checkFree() {
        if (getCountModules() >= getCountPorts())
            throw std::invalid_argument("Count of modules exceeds count of ports");
    }

    void Observation_Center::setGenerator(unsigned int prod) {
        checkFree();

        std::cout << "Setting generator" << std::endl;

    }

    ///////////////////////////////

    bool operator<(const Map_Object &left, const Map_Object &right){
        if (left.position.x < right.position.x)
            return true;
        else if(left.position.x == right.position.x)
            return left.position.y < right.position.y;
        else
            return false;
    }

    void Quick_Navigator::add(Map_Object * qObj) {
//        objectTree.insert(std::pair<coordinates, Map_Object*>(qObj->getPosition(), qObj));
    }
}
