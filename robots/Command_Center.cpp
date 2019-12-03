#include "Command_Center.h"
#include "Environment_describer.h"

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
        chooseManModule();

        int top_cor, left_cor, bottom_cor, right_cor;
        determineCorers(top_cor, left_cor, bottom_cor, right_cor, matchMan->getRadius());

        std::cout << "Finding SUBJECTS:" << std::endl;
        for (int h = top_cor; h >= bottom_cor; --h) {
            for (int w = left_cor; w <= right_cor; ++w) {
                if (getX() != w || getY() != h) {
                    coordinates thisPoint { static_cast<unsigned int>(w), static_cast<unsigned int>(h) };
                    Map_Object * thereObj = env->checkStaticPoint(thisPoint);
                    if (thereObj != nullptr) {
                        if (!strcmp(typeid(*thereObj).name(), "N4robo18Observation_CenterE") ||
                        (!strcmp(typeid(*thereObj).name(), "N4robo14Command_CenterE") &&
                         !dynamic_cast<Command_Center *>(thereObj)->isManager())) {
                            //std::cout << " { " << thereObj->getX() << ", " << thereObj->getY() << " } - "
                            //          << typeid(*thereObj).name() << std::endl;

                            auto * subo = dynamic_cast<Observation_Center *>(thereObj);
                            if (subo->getOwner() != nullptr) {
                                if (matchMan->addSubord(subo)) { //hold iterator!!!!
                                    return 1;
                                }

                                subo->setOwner(this);
                            }
                        }
                    }
                }
            }
        }

        return 0;
    }

    int Command_Center::chooseManModule() {
        Managing * man;
        unsigned int matchRad = 0;
        matchMan = nullptr;

        for (auto & module : modules) {
            if(!strcmp(typeid(*module).name(), "N4robo8ManagingE") && module->getActive()) {
                man = static_cast<Managing *>(module);
                if (man->getRadius() > matchRad && man->getActive()) {
                    matchRad = man->getRadius();
                    matchMan = man;
                }
            }
        }

        if (matchMan == nullptr)
            return 1; //no active managing modules

        return 0;
    }
}