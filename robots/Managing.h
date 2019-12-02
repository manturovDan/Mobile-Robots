#ifndef ROBOTSCREATE_MANAGING_H
#define ROBOTSCREATE_MANAGING_H

#include "Observation_Center.h"
#include "Energy_Consumer.h"

namespace robo {
    class Managing : public Energy_Consumer {
    public:
        Managing() = delete;
        Managing(unsigned int rad, unsigned int consumption, unsigned int priority, unsigned int subs) :
                radius(rad), subs_count(subs), Energy_Consumer(consumption, priority, false) {  }
    protected:
        unsigned int radius;
        unsigned int subs_count;
        std::vector<Observation_Center *> subordinate;
    };
}

#endif //ROBOTSCREATE_MANAGING_H
