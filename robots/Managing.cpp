#include "Managing.h"
#include "Ai_Deep.h"

namespace robo {
    Ai_Deep * Managing::ai;
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

    void Managing::reportAI(Robot_Scout * reporter, int type) {
        ai->makeReport(reporter, type);
    }

    void Managing::setAI(Ai_Deep *aip) {
        ai = aip;
    }

    bool Managing::unknownSquare(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor) {
        for (int h = top_cor; h >= bottom_cor && h <= top_cor; --h) {
            for (int w = left_cor; w <= right_cor; ++w) {
                if (!checkPoint({static_cast<unsigned int>(w), static_cast<unsigned int>(h)}))
                    return true;
            }
        }
        return false;
    }

    bool Managing::checkPoint(coordinates pos) {
        return ai->isOpened(pos);
    }

    void Managing::addStep(Robot_Scout * who, coordinates pos, int dir, unsigned int time, int report) {
        ai->getMd()->addStep({who, pos, dir, time, report});
    }
}