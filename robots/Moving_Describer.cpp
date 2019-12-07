#include "Moving_Describer.h"

namespace robo {
    int Moving_Describer::addStep(robo::moment mom) {
        for (auto & it : move_d) {
            if (it.pos == mom.pos && it.time == mom.time)
                return 1;
        }

        move_d.push_back(mom);
    }
}