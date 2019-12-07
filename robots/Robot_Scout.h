#ifndef ROBOTSCREATE_ROBOT_SCOUT_H
#define ROBOTSCREATE_ROBOT_SCOUT_H

#include <vector>

#include "Observation_Center.h"

namespace robo {
/// @blocked - true if object is moving and we cant check it in the tree
    class Robot_Scout : virtual public Observation_Center {
    protected:
        bool blocked;
        int direction;
    public:
        Robot_Scout(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &);
        bool getBlocked() { return blocked; }
        void unBlock() { blocked = false; }
        void move(coordinates, int);

        std::string whoami() override;
    };
}

#endif //ROBOTSCREATE_ROBOT_SCOUT_H
