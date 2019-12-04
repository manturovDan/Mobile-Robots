#ifndef ROBOTSCREATE_ROBOT_COMMANDER_H
#define ROBOTSCREATE_ROBOT_COMMANDER_H

#include <vector>

#include "Robot_Scout.h"
#include "Command_Center.h"
#include "Module.h"

namespace robo {
    class Robot_Commander : public Robot_Scout, Command_Center {
    public:
        Robot_Commander(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &, unsigned int);

        std::string whoami() override ;
    };
}
#endif //ROBOTSCREATE_ROBOT_COMMANDER_H
