#include "Command_Center.h"
#include "Robot_Commander.h"

namespace robo {
    Robot_Commander::Robot_Commander(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods, std::string & desc, unsigned int speed)
    : Command_Center(ports, consumption, price, mods, desc, {0, 0}),
    Robot_Scout(ports, consumption, price, mods, desc, speed), Observation_Center(ports, consumption, price, mods, desc) {}

    std::string Robot_Commander::whoami() {
        std::stringstream ss;
        std::string host = owner != nullptr ? owner->getDescription() : "none";

        ss << "Object : Robot_Commander: {" << position.x << ", " << position.y << "}\nDesc: '" << description << "';\n"
                                         "Consumption: " << energyConsumption << ";\nCost: " << cost << ";\n"
                                         "PortsCount: " << countPorts << ";\nAppeared: " << appeared << ";\n"
                                         "Blocked: " << blocked << "\n"
                                         "Speed: " << speed << ";\nOwner = " << host << std::endl;
        ss << "Modules:\n" << myModules() << std::endl;
        return ss.str();
    }
}