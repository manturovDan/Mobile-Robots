#include "Moving_Describer.h"

namespace robo {
    int Moving_Describer::addStep(robo::moment mom) {
        for (auto & it : move_d) {
            if (it.pos == mom.pos && it.time == mom.time)
                return 1;
        }

        move_d.push_back(mom);
    }

    void Moving_Describer::printSteps(std::ostream & stream) {
        stream << "--------------\nMOVING:\n--------------" << std::endl;
        for (auto & it : move_d) {
            std::cout << "Robot: " << it.moving_obj->getDescription() << "; target_position: {" << it.pos.x << "; " <<
            it.pos.y << "}; direction: " << it.direction << "target_time: " << it.time << "; dest: " << it.destination << std::endl;
        }
    }
}