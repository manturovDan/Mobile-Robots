#ifndef ROBOTSCREATE_ROBOT_COMMANDER_H
#define ROBOTSCREATE_ROBOT_COMMANDER_H

#include <vector>

#include "Robot_Scout.h"
#include "Command_Center.h"
#include "Module.h"

namespace robo {
    class Robot_Commander : public Robot_Scout, public Command_Center {
    public:
        Robot_Commander(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &);
        int connectScout(Robot_Scout *);
        std::string whoami() override;
        Robot_Scout * getPair() const;
        std::map<coordinates, Map_Object *> research() override;
        ///radius of impact = radius of managing module + radius of pair's sensor
        unsigned int ri() const;
    };
}
#endif //ROBOTSCREATE_ROBOT_COMMANDER_H
