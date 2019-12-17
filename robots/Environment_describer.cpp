#include "Environment_describer.h"

namespace robo {
    Environment_describer::Environment_describer(int widthG, int heightG) : Environment_describer() {
        if (widthG > 1000 || widthG < 10 || heightG > 1000 || heightG < 10)
            throw std::invalid_argument("Incorrect map params!");
        width = widthG;
        height = heightG;
    }

    int Environment_describer::setWidthHeight(int newVal, bool coord) {
        if (newVal > 1000 || newVal < 10)
            throw std::invalid_argument("Incorrect map params!");

        unsigned int prev;
        if (coord) {
            prev = width;
            width = newVal;
        }
        else {
            prev = height;
            height = newVal;
        }

        for(robo::Env_Consistent_Iter it = begin(); it != end(); ++it) {
            if ((*it)->getX() >= width || (*it)->getY()>= height) {
                if (coord)
                    width = prev;
                else
                    height = prev;
                throw std::invalid_argument("Incorrect map resizing");
            }
        }

        return 0;
    }


    Map_Object * Environment_describer::setObject(Characters objType, robo::coordinates position) {
        if (position.x >= width || position.y >= height)
            throw std::invalid_argument("Incorrect object coordinates!");

        Map_Object * nw_obj = nullptr;
        try {
            if (objType == Obstacle_t) {
                nw_obj = new Obstacle(position);
            } else if (objType == Interest_t) {
                nw_obj = new Interest_Point(position);
            } else {
                throw std::invalid_argument("Unknown object tries to penetrate in my laboratory work (nature)");
            }
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw std::invalid_argument("Incorrect object tries to penetrate in my laboratory work (nature)");
        }

        map_obj.push_back(nw_obj);

        return nw_obj;
    }


    Map_Object * Environment_describer::setObject(Characters objType, unsigned int ports, unsigned int consumption,
            int price, std::vector<robo::Module *> & modules, std::string & desc) {

        Map_Object *nw_obj = nullptr;
        try {
            if (objType == Robot_Commander_t) {
                nw_obj = new Robot_Commander(ports, consumption, price, modules, desc);
            } else if (objType == Robot_Scout_t) {
                nw_obj = new Robot_Scout(ports, consumption, price, modules, desc);
            } else {
                throw std::invalid_argument("Unknown object tries to penetrate in my laboratory work (moving)");
            }
        } catch (std::exception &e) {
            throw std::invalid_argument("Incorrect object tries to penetrate in my laboratory work (moving)");
        }

        map_obj.push_back(nw_obj);

        return nw_obj;
    }

    Map_Object * Environment_describer::setObject(Characters objType, unsigned int ports, unsigned int consumption,
                  int price, std::vector<robo::Module *> & modules, std::string & desc, coordinates pos) {
        Map_Object * nw_obj = nullptr;
        if (objType == Command_Center_t) {
            nw_obj = new Command_Center(ports, consumption, price, modules, desc, pos);
        } else if (objType == Observation_Center_t) {
            nw_obj = new Observation_Center(ports, consumption, price, modules, desc, pos);
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

    Map_Object * Environment_describer::checkStaticPoint(coordinates point) {
        //TODO maybe to do with multimap in the future
        auto it = begin();
        for (; it != end(); ++it) {
            if ((*it)->getPosition() == point && strcmp(typeid(**it).name(), "N4robo15Robot_CommanderE") != 0 && strcmp(typeid(**it).name(), "N4robo11Robot_ScoutE") != 0) {
                break;
            }
        }

        if (it == end())
            return nullptr;
        return *it;

    }

    Map_Object * Environment_describer::checkMobOnPoint(coordinates point) {
        auto it = begin();
        for (; it != end(); ++it) {
            if ((*it)->getPosition() == point && !dynamic_cast<Robot_Scout *>(*it)->getBlocked() &&
                (strcmp(typeid(**it).name(), "N4robo15Robot_CommanderE") == 0 || strcmp(typeid(**it).name(), "N4robo11Robot_ScoutE") == 0)) {
                break;
            }
        }

        if (it == end())
            return nullptr;
        return *it;
    }

    bool Environment_describer::isBoundary(coordinates point) {
        if (point.x == 0 || point.y == 0)
            return true;
        return point.x == width - 1 || point.y == height - 1;
    }

    bool Environment_describer::isTopBoundary(coordinates point) {
        return point.y == height - 1;
    }

    bool Environment_describer::isRightBoundary(coordinates point) {
        return point.x == width - 1;
    }

    Env_Consistent_Iter Env_Consistent_Iter::operator++(int) { //postfix
        auto retit = Env_Consistent_Iter(iter);
        iter++;
        return retit;
    }

    Env_Consistent_Iter & Env_Consistent_Iter::operator++() { //prefix
        iter++;
        return *this;
    }

    Map_Object * Env_Consistent_Iter::operator*() {
        return *iter;
    }
}