#ifndef ROBOTSCREATE_ENERGY_CONSUMER_H
#define ROBOTSCREATE_ENERGY_CONSUMER_H

#include "Module.h"

namespace robo {
    class Energy_Consumer : public Module {
    public:
        virtual unsigned int getRadius() = 0;
        int getConsumption() const { return powerConsumption; }
    protected:
        Energy_Consumer() = delete;
        Energy_Consumer(unsigned int cons, unsigned int prior, bool act = true) : powerConsumption(cons), Module(prior, act) {}
        int powerConsumption;
        ~Energy_Consumer() override = default;
    };
}

#endif //ROBOTSCREATE_ENERGY_CONSUMER_H
