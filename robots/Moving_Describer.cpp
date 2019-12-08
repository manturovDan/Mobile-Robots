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
            it.pos.y << "}; direction: " << it.direction << "; target_time: " << it.time << "; dest: " << it.destination << std::endl;
        }
    }

    void Moving_Describer::makeSteps(unsigned int curTime) {
        std::vector<std::deque<moment>::iterator> delev;
        for (auto it = move_d.begin(); it != move_d.end(); ++ it) {
            if (it->time < curTime)
                throw std::invalid_argument("ROBOTIME error");
            if (it->time == curTime) {
                it->moving_obj->move(it->pos, it->direction);
                if(it->destination != 0)
                    it->moving_obj->report(it->destination);
                delev.push_back(it);
            }
        }

        for (auto dit : delev) {
            move_d.erase(dit);
        }
    }

    bool Moving_Describer::isMoving(Robot_Scout * scout) {
        for (auto it = move_d.begin(); it != move_d.end(); ++ it) {
            if (it->moving_obj == scout)
                return true;
        }

        return false;
    }

}