#include "Command_Center.h"
#include "Robot_Commander.h"

namespace robo {
    Robot_Commander::Robot_Commander(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods, std::string & desc)
    : Command_Center(ports, consumption, price, mods, desc, {0, 0}),
    Robot_Scout(ports, consumption, price, mods, desc), Observation_Center(ports, consumption, price, mods, desc) {}

    std::string Robot_Commander::whoami() {
        std::stringstream ss;
        std::string host = owner != nullptr ? owner->getDescription() : "none";

        ss << "Object : Robot_Commander: {" << position.x << ", " << position.y << "}\nDesc: '" << description << "';\n"
                                         "Consumption: " << energyConsumption << ";\nCost: " << cost << ";\n"
                                         "PortsCount: " << countPorts << ";\nAppeared: " << appeared << ";\n"
                                         "Blocked: " << blocked << "\n"
                                         "Owner = " << host << "\nReal Manager: " << real_manager << std::endl;
        ss << "Modules:\n" << myModules() << std::endl;
        return ss.str();
    }

    int Robot_Commander::connectScout(Robot_Scout * sco) {
        if (sco->getOwner() == nullptr) {
            if (matchMan->addSubord(sco)) {
                return 1;
            }

            sco->setOwner(this);
            setOwner(this);
            return 0;

        }
        return 1;
    }

    Robot_Scout * Robot_Commander::getPair() {
        for(auto it : *manMod()) {
            if (it->getOwner() == this) {
                return dynamic_cast<Robot_Scout *>(it);
            }
        }

        return nullptr;
    }
}