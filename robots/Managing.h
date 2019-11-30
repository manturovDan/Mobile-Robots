#ifndef ROBOTSCREATE_MANAGING_H
#define ROBOTSCREATE_MANAGING_H

#include "Energy_Consumer.h"

namespace robo {
    class Managing : public Energy_Consumer {
    public:
        Managing() = delete;
        Managing(unsigned int rad, unsigned int consumption, unsigned int priority, unsigned int subs) :
                radius(rad), Energy_Consumer(consumption, priority, false) {  }
    protected:
        unsigned int radius;
        //std::vector<Robo_Component *> subordinate;
    };
}

#endif //ROBOTSCREATE_MANAGING_H
