#include "Command_Center.h"

namespace robo {
    Command_Center::Command_Center(unsigned int ports, unsigned int consumption, int price,
                                   std::vector<Module *> & mods, std::string & desc, robo::coordinates pos) : Observation_Center(ports, consumption, price, mods, desc, pos) {
        //TODO check if there is one or more managing modules
    }

    std::string Command_Center::whoami() {
        std::stringstream ss;
        ss << "Object : Command_Center: {" << position.x << ", " << position.y << "}\nDesc: '" << description << "';\n"
                                        "Consumption: " << energyConsumption << ";\nCost: " << cost << ";\n"
                                        "PortsCount: " << countPorts << ";\nAppeared: " << appeared << std::endl;
        return ss.str();
    }

    int Command_Center::subdue() {
        Managing * man;
        unsigned int matchRad = 0;
        Managing * matchMan = nullptr;
        for (auto & module : modules) {
            if(!strcmp(typeid(*module).name(), "N4robo8ManagingE") && module->getActive()) {
                man = static_cast<Managing *>(module);
                if (man->getRadius() > matchRad && man->getActive())
                    matchMan = man;
            }
        }

        if (matchMan == nullptr)
            return 1; //no active managing modules

        int top_cor, left_cor, bottom_cor, right_cor;
        determineCorers(top_cor, left_cor, bottom_cor, right_cor, matchMan->getRadius());

        std::cout << "Finding SUBJECTS:" << std::endl;
        for (int h = top_cor; h >= bottom_cor; --h) {
            for (int w = left_cor; w <= right_cor; ++w) {
                if (getX() == w && getY() == h)
                    std::cout << " ########## ";
                else
                    std::cout << " { " << w << ", " << h << " } "; // THERE MAY BE SUBORDINATES
            }
            std::cout << std::endl;
        }

        return 0;
    }
}