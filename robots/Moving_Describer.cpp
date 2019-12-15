#include "Moving_Describer.h"

namespace robo {
    int Moving_Describer::addStep(robo::moment mom) {
        for (auto & it : move_d) {
            if (it.pos == mom.pos && it.time == mom.time)
                return 1;
        }

        move_d.push_back(mom);

        return 0;
    }

    void Moving_Describer::printSteps(std::ostream & stream) {
        return;
        stream << "--------------\nMOVING:\n--------------" << std::endl;
        for (auto & it : move_d) {
            if(it.moving_obj == nullptr)
                continue;
            std::cout << "Robot: " << it.moving_obj->getDescription() << "; target_position: {" << it.pos.x << "; " <<
            it.pos.y << "}; direction: " << it.direction << "; target_time: " << it.time << "; dest: " << it.destination << std::endl;
        }
    }

    int Moving_Describer::makeSteps(unsigned int curTime) {
        std::vector<std::deque<moment>::iterator> delev;
        for (auto it = move_d.begin(); it != move_d.end(); ++it) {
            if(it->moving_obj == nullptr)
                continue;

            if (it->time < curTime)
                throw std::invalid_argument("ROBOTIME error");
            if (it->time == curTime) {
                //std:: cout << curTime << " ";
                it->moving_obj->move(it->pos, it->direction);
                if(it->destination != 0)
                    it->moving_obj->report(it->destination);
                it->moving_obj = nullptr;
                //delev.push_back(it);
            }
        }

        //std::cout << "SECOND " << curTime << std::endl;
        for (auto dit : delev) { //not iter
            std::cout << "Robot: " << dit->moving_obj->getDescription() << "; target_position: {" << dit->pos.x << "; " <<
            dit->pos.y << "}; direction: " << dit->direction << "; target_time: " << dit->time << "; dest: " << dit->destination << std::endl;
            move_d.erase(dit);
        }
        //std::cout << "---------------------" <<std::endl;
        return 0;
    }

    bool Moving_Describer::isMoving(Robot_Scout * scout) {
        for (auto it = move_d.begin(); it != move_d.end(); ++ it) {
            if (it->moving_obj == scout)
                return true;
        }

        return false;
    }

    unsigned int Moving_Describer::routePoint(Robot_Scout * mobile, coordinates pos, int destination, unsigned int curTime) {
        unsigned int assumeTime = curTime + 1;
        int lastDir = mobile->getDirection();
        coordinates lastPos = mobile->getPosition();
        for(auto & it : move_d) {
            if (it.moving_obj == mobile && assumeTime <= it.time) {
                assumeTime = it.time + 1;
                lastDir = it.direction;
                lastPos = it.pos;
            }
        }

        int tarDir = 0;
        if (lastPos.x - pos.x == 1 && lastPos.y == pos.y)
            tarDir = 1;
        else if (lastPos.x - pos.x == -1 && lastPos.y == pos.y)
            tarDir = 3;
        else if (lastPos.y - pos.y == -1 && lastPos.x == pos.x)
            tarDir = 0;
        else if (lastPos.y - pos.y == 1 && lastPos.x == pos.x)
            tarDir = 2;
        else if (lastPos.x == pos.x && lastPos.y == pos.y) {
            return assumeTime;
        }
        else {
            std::cout << lastPos.x << " " << pos.x << " " << lastPos.y << " " <<  pos.y << std::endl;
            throw std::invalid_argument("Unknown direction");
        }

        assumeTime = setDirection(mobile, lastPos, tarDir, lastDir, assumeTime, 2);

        bool isRoute = false;
        while (!isRoute) {
            int watched = 0;
            for(auto & it : move_d) {
                if (it.pos == pos && assumeTime == it.time) {
                    ++assumeTime;
                    watched = 0;
                    break;
                }
                ++watched;
            }

            if (watched == move_d.size())
                isRoute = true;
        }


        //TODO if object stops on the point it must make it blocked and previously check if no routs have his point

        addStep({mobile, pos, tarDir, assumeTime, destination});

        return assumeTime;
    }

    unsigned int Moving_Describer::setDirection(Robot_Scout * mobile, coordinates pos, int tarDir, int initDir, unsigned int turnTime, int destination) {
        if (initDir == tarDir)
            return turnTime;
        if (initDir == 0) {
            if (tarDir == 2) {
                addStep({mobile, pos, 1, turnTime++, destination});
                addStep({mobile, pos, 2, turnTime, destination});
            } else
                addStep({mobile, pos, tarDir, turnTime, destination});
        } else if (initDir == 1) {
            if (tarDir == 3) {
                addStep({mobile, pos, 2, turnTime++, destination});
                addStep({mobile, pos, 3, turnTime, destination});
            } else
                addStep({mobile, pos, tarDir, turnTime, destination});
        } else if (initDir == 2) {
            if (tarDir == 0) {
                addStep({mobile, pos, 2, turnTime++, destination});
                addStep({mobile, pos, 0, turnTime, destination});
            } else
                addStep({mobile, pos, tarDir, turnTime, destination});
        } else {
            if (tarDir == 1) {
                addStep({mobile, pos, 0, turnTime++, destination});
                addStep({mobile, pos, 1, turnTime, destination});
            } else
                addStep({mobile, pos, tarDir, turnTime, destination});
        }

        return turnTime+1;
    }

    bool Moving_Describer::onRoute(coordinates tar) const {
        for (auto & it : move_d) {
            if (it.pos == tar)
                return true;
        }

        return false;
    }

}