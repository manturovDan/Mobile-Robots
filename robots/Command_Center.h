#ifndef ROBOTSCREATE_COMMAND_CENTER_H
#define ROBOTSCREATE_COMMAND_CENTER_H

#include <vector>

#include "Observation_Center.h"
#include "Managing.h"

namespace robo {
    class Command_Center : virtual public Observation_Center {
    protected:
        bool real_manager = true; //TODO in depend of consumption
    public:
        Command_Center(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &, coordinates);
        std::string whoami() override;
        int subdue();
        bool isManager() { return real_manager; }
    };
}

#endif //ROBOTSCREATE_COMMAND_CENTER_H
