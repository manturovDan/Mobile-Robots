#include "Observation_Center.h"

namespace robo {
    Observation_Center::Observation_Center(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods,
                                           std::string & desc, coordinates pos) : Map_Object(pos), description(desc), cost(price), countPorts(ports), energyConsumption(consumption), appeared(true) {
        initModules(mods);
    }

    void Observation_Center::initModules(const std::vector<Module *> & modul) {
        if (countPorts < modul.size())
            throw std::invalid_argument("Robot has too many modules");

        for (auto itm : modul) {
            modules.push_back((*itm).copy());
        }
    }

    void Observation_Center::checkFree() {
        if (getCountModules() >= getCountPorts())
            throw std::invalid_argument("Count of modules exceeds count of ports");
    }

    std::string Observation_Center::whoami() {
        std::stringstream ss;
        ss << "Object : Observation_Center: {" << position.x << ", " << position.y << "}\nDesc: '" << description << "';\n"
                                           "Consumption: " << energyConsumption << ";\nCost: " << cost << ";\n"
                                           "PortsCount: " << countPorts << ";\nAppeared: " << appeared << std::endl;
        return ss.str();
    }

    int Observation_Center::look() {
        for (auto it = modules.begin(); it != modules.end(); ++it) {
            std::cout << typeid(**it).name() << std::endl;
        }
    }
}