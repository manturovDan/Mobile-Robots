#ifndef ROBOTSCREATE_COMMAND_CENTER_H
#define ROBOTSCREATE_COMMAND_CENTER_H

#include <vector>

#include "Observation_Center.h"
#include "Managing.h"

namespace robo {
    class Command_Center : virtual public Observation_Center {
    protected:
        bool real_manager = true;
        Managing * matchMan;
    public:
        Command_Center(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &, coordinates pos = {0, 2});
        std::string whoami() override;
        int subdue();
        bool isManager() { return real_manager; }
        virtual std::map<coordinates, Map_Object *> research();
        Managing * manMod() const { return matchMan; }
        int chooseManModule();;
        void comReport(Robot_Scout *, int);
    };
}

#endif //ROBOTSCREATE_COMMAND_CENTER_H
