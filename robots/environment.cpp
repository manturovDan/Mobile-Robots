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


    Map_Object * Environment_describer::setObject(robo::coordinates position, Characters objType) {
        if (position.x >= width || position.y >= height)
            throw std::invalid_argument("Incorrect object coordinates!");

        Map_Object * nw_obj = nullptr;
        if (objType == Obstacle_t) {
            nw_obj = new Obstacle(position);
        } else if (objType == Interest_t) {
            nw_obj = new Interest_Point(position);
        } else {
            throw std::invalid_argument("Unknown object tries to penetrate in my laboratory work (nature)");
        }

        map_obj.push_back(nw_obj); // OR COPY????
        //qTree.add(nw_obj);

        return nw_obj;
    }

    Map_Object * Environment_describer::setObject(unsigned int ports, unsigned int consumption, int price, std::vector<robo::Module *> & modules, Characters objType, std::string & desc) {
        Map_Object * nw_obj = nullptr;
        if (objType == Robot_Commander_t) {
            nw_obj = new Robot_Commander(ports, consumption, price, modules, desc);
        } else if (objType == Robot_Scout_t) {
            nw_obj = new Robot_Scout(ports, consumption, price, modules, desc);
        } else {
            throw std::invalid_argument("Unknown object tries to penetrate in my laboratory work (moving)");
        }

        map_obj.push_back(nw_obj);

        return nw_obj;
    }

    Map_Object * Environment_describer::setObject(coordinates pos, unsigned int ports, unsigned int consumption, int price, std::vector<robo::Module *> & modules, Characters objType, std::string & desc) {
        Map_Object * nw_obj = nullptr;
        if (objType == Command_Center_t) {
            nw_obj = new Command_Center(pos, ports, consumption, price, modules, desc);
        } else if (objType == Observation_Center_t) {
            nw_obj = new Observation_Center(pos, ports, consumption, price, modules, desc);
        } else {
            throw std::invalid_argument("Unknown object tries to penetrate in my laboratory work (static)");
        }

        map_obj.push_back(nw_obj);
        return nw_obj;
    }

    void Environment_describer::print(std::ostream & stream) {
        for (auto & it : map_obj) {
            it->print();
        }
    }

    ///////////////////////////////

    void Observation_Center::initModules(std::vector<Module *> & modul) {
        if (countPorts < modul.size())
            throw std::invalid_argument("Robot has too many modules");

        for (auto itm : modul) {
            modules.push_back((*itm).copy());
        }
    }

    Observation_Center::Observation_Center(coordinates pos, unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods,
                                           std::string & desc) : Map_Object(pos), description(desc), cost(price), countPorts(ports), energyConsumption(consumption), appeared(true) {
        initModules(mods);
    }

    Observation_Center::Observation_Center(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods,
            std::string & desc) : Map_Object(), description(desc), cost(price), countPorts(ports), energyConsumption(consumption), appeared(true) {
        initModules(mods);
    }

    Map_Object::Map_Object(robo::coordinates pos) : position(pos), appeared(true) {
        if (pos.x >= env->getWidth() || pos.y >= env->getHeight())
            throw std::invalid_argument("x or y is over the Map");
        //check collision
    }

    void Observation_Center::checkFree() {
        if (getCountModules() >= getCountPorts())
            throw std::invalid_argument("Count of modules exceeds count of ports");
    }

    ///////////////////////////////////

    Robot_Scout::Robot_Scout(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods,
            std::string & desc) : Observation_Center(ports, consumption, price, mods, desc) {

    }

    ///////////////////////////////

    Command_Center::Command_Center(robo::coordinates pos, unsigned int ports, unsigned int consumption, int price,
            std::vector<Module *> & mods, std::string & desc) : Observation_Center(pos, ports, consumption, price, mods, desc) {
        //check if there is one or more managing modules
    }

    ///////////////////////////////////

    Robot_Commander::Robot_Commander(unsigned int ports, unsigned int consumption, int price,
                                    std::vector<Module *> & mods, std::string & desc) : Command_Center({0, 0},
                                            ports, consumption, price, mods, desc), Robot_Scout(ports, consumption, price,
                                                    mods, desc), Observation_Center(ports, consumption, price, mods, desc) {}

    ///////////////////////////

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
