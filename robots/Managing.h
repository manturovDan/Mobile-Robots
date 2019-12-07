#ifndef ROBOTSCREATE_MANAGING_H
#define ROBOTSCREATE_MANAGING_H

#include <algorithm>
#include <sstream>

#include "Observation_Center.h"
#include "Energy_Consumer.h"
#include "Robot_Scout.h"
#include "Ai_Deep.h"

namespace robo {
    class Ai_Deep;
    class Managing : public Energy_Consumer {
    public:
        Managing() = delete;
        Managing(unsigned int rad, unsigned int consumption, unsigned int priority, unsigned int subs) :
                radius(rad), subs_count(subs), Energy_Consumer(consumption, priority, true) {}
        Module * copy() override;
        unsigned int getRadius() { return radius; }
        int addSubord(Observation_Center *);
        std::string whoami() override;
        int subord_count() { return subordinate.size(); }
        std::vector<Observation_Center *>::const_iterator begin() { return subordinate.begin(); }
        std::vector<Observation_Center *>::const_iterator end() { return subordinate.end(); }
        void reportAI(Robot_Scout *, int);
        static void setAI(Ai_Deep * aip);
    protected:
        unsigned int radius;
        unsigned int subs_count;
        std::vector<Observation_Center *> subordinate;
        static Ai_Deep * ai;
    };
}

#endif //ROBOTSCREATE_MANAGING_H
