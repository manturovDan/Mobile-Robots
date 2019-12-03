#include "Robot_Scout.h"
#include "Observation_Center.h"

namespace robo {
    Robot_Scout::Robot_Scout(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods,
            std::string & desc, unsigned int spd) : speed(spd), blocked(false),
            Observation_Center(ports, consumption, price, mods, desc) {}

    std::string Robot_Scout::whoami() {
        std::stringstream ss;
        ss << "Object : Robot_Scout: {" << position.x << ", " << position.y << "}\nDesc: '" << description << "';\n"
                                     "Consumption: " << energyConsumption << ";\nCost: " << cost << ";\n"
                                      "PortsCount: " << countPorts << ";\nAppeared: " << appeared << ";\n"
                                      "Blocked: " << blocked << "\n"
                                      "Speed: " << speed <<std::endl;
        return ss.str();
    }
}