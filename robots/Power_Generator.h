#ifndef ROBOTSCREATE_POWER_GENERATOR_H
#define ROBOTSCREATE_POWER_GENERATOR_H

#include <string>
#include <sstream>

#include "Module.h"

namespace robo {
    class Power_Generator: public Module {
    public:
        Power_Generator(int prior, unsigned int prod, bool act = true) : Module(prior, act), energyProduction(prod) {}
        Module * copy() override;
        std::string whoami() override;
        unsigned int getProduction() const { return energyProduction; }
        ~Power_Generator() override = default;
    protected:
        int energyProduction;
    };
}

#endif //ROBOTSCREATE_POWER_GENERATOR_H
