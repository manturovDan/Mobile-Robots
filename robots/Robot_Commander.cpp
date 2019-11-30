#include "Command_Center.h"
#include "Robot_Commander.h"

namespace robo {
    Robot_Commander::Robot_Commander(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods, std::string & desc, unsigned int speed)
    : Command_Center(ports, consumption, price, mods, desc, {0, 0}),
    Robot_Scout(ports, consumption, price, mods, desc, speed), Observation_Center(ports, consumption, price, mods, desc) {}
}