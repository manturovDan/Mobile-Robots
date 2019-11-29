#ifndef ROBOTSCREATE_COMMAND_CENTER_H
#define ROBOTSCREATE_COMMAND_CENTER_H

#include <vector>

#include "Observation_Center.h"

namespace robo {
    class Command_Center : virtual public Observation_Center {
    public:
        Command_Center(coordinates, unsigned int, unsigned int, int, std::vector<Module *> &, std::string &);
    };
}

#endif //ROBOTSCREATE_COMMAND_CENTER_H
