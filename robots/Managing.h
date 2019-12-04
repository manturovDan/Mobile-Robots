#ifndef ROBOTSCREATE_MANAGING_H
#define ROBOTSCREATE_MANAGING_H

#include <algorithm>
#include <sstream>

#include "Observation_Center.h"
#include "Energy_Consumer.h"

namespace robo {
    class Managing : public Energy_Consumer {
    public:
        Managing() = delete;
        Managing(unsigned int rad, unsigned int consumption, unsigned int priority, unsigned int subs) :
                radius(rad), subs_count(subs), Energy_Consumer(consumption, priority, true) {}
        Module * copy() override;
        unsigned int getRadius() { return radius; }
        int addSubord(Observation_Center *);
        std::string whoami() override;

    protected:
        unsigned int radius;
        unsigned int subs_count;
        std::vector<Observation_Center *> subordinate;
    };
}

#endif //ROBOTSCREATE_MANAGING_H
