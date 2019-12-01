#ifndef ROBOTSCREATE_COMMAND_CENTER_H
#define ROBOTSCREATE_COMMAND_CENTER_H

#include <vector>

#include "Observation_Center.h"
#include "Module.h"

namespace robo {
    class Command_Center : virtual public Observation_Center {
    public:
        Command_Center(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &, coordinates);
        std::string whoami();
    };
}

#endif //ROBOTSCREATE_COMMAND_CENTER_H
