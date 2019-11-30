#include "Robot_Scout.h"
#include "Observation_Center.h"

namespace robo {
    Robot_Scout::Robot_Scout(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods,
                             std::string & desc, unsigned int speed) : Observation_Center(ports, consumption, price, mods, desc) {

    }
}