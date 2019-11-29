#ifndef ROBOTSCREATE_ROBOT_COMMANDER_H
#define ROBOTSCREATE_ROBOT_COMMANDER_H

#include <vector>

#include "Robot_Scout.h"
#include "Command_Center.h"

namespace robo {
    class Robot_Commander : public Robot_Scout, Command_Center {
    public:
        Robot_Commander(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &);
    };
}
#endif //ROBOTSCREATE_ROBOT_COMMANDER_H
