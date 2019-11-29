#ifndef ROBOTSCREATE_POWER_GENERATOR_H
#define ROBOTSCREATE_POWER_GENERATOR_H

#include "Module.h"

namespace robo {
    class Energy_Consumer : public Module {
    protected:
        Energy_Consumer() = delete;
        Energy_Consumer(unsigned int cons, unsigned int prior, bool act = true) : powerConsumption(cons), Module(prior, act) {}
        int powerConsumption;
    };
}

#endif //ROBOTSCREATE_POWER_GENERATOR_H
