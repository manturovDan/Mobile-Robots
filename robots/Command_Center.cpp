#include "Command_Center.h"

namespace robo {
    Command_Center::Command_Center(unsigned int ports, unsigned int consumption, int price,
                                   std::vector<Module *> & mods, std::string & desc, robo::coordinates pos) : Observation_Center(ports, consumption, price, mods, desc, pos) {
        //check if there is one or more managing modules
    }
}