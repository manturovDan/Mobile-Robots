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
                radius(rad), subs_count(subs), Energy_Consumer(consumption, priority, true) { if (rad == 0 || subs == 0) throw std::invalid_argument("Incorrect managing radius or subs count"); }
        Module * copy() override;
        unsigned int getRadius() override { return radius; }
        int addSubord(Observation_Center *);
        std::string whoami() override;
        int subord_count() { return subordinate.size(); }

        std::vector<Observation_Center *>::const_iterator begin() { return subordinate.begin(); }
        std::vector<Observation_Center *>::const_iterator end() { return subordinate.end(); }
        bool checkPoint(coordinates);
        bool unknownSquare(unsigned int, unsigned int, unsigned int, unsigned int);
        void reportAI(Robot_Scout *, int);
        void addStep(Robot_Scout *, coordinates, int, unsigned int, int);
        static void setAI(Ai_Deep * aip);
        ~Managing() = default;
    protected:
        unsigned int radius;
        unsigned int subs_count;
        std::vector<Observation_Center *> subordinate;
        static Ai_Deep * ai;
    };
}

#endif //ROBOTSCREATE_MANAGING_H
