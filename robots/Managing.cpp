#include "Managing.h"

namespace robo {
    Module * Managing::copy() {
        auto nw_mm = new Managing(radius, powerConsumption, priority, subs_count);
        return nw_mm;
    }

    int Managing::addSubord(Observation_Center * sub) {
        if (subs_count == subordinate.size())
            return 1; //busy

        if(std::find(subordinate.begin(), subordinate.end(), sub) != subordinate.end())
            return 2; //this is already subordinating

        subordinate.push_back(sub);

        return 0;
    }

    std::string Managing::whoami() {
        std::stringstream ss;
        ss << "\tManaging maximum_subordinates_count = " << subs_count <<" radius = " << radius << " powerConsumption = " << powerConsumption << " priority = " << priority << " active = " << active << ":" << std::endl;
        for (auto sub : subordinate) {
            if (sub == nullptr)
                continue;
            ss << "\t\ts) " << sub->getDescription();
        }
        return ss.str();
    }
}