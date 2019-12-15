#ifndef ROBOTSCREATE_MOVING_DESCRIBER_H
#define ROBOTSCREATE_MOVING_DESCRIBER_H

#include <deque>

#include "Robot_Scout.h"

namespace robo {
    /// destination == 0 - nothing to do, moving is continue; 1 - commander has arrived to 0,1 - need a subordinate;
    /// 2 - commander/scout is moving/rotating to task point;
    /// 3 - commander has arrived to new point; -1 - is waiting for deleting;
    /// 4 - arrived commander is ready for full area researching (READY FOR PairRes)
    /// 5 - subordinate has arrived to grey point; 55 - revolved
    /// 6 - subordinate has ended the researching and must move to init
    /// 7 - subordinate has backed to owner and should be turned
    /// 8 - sends subordinate when area is researching
    /// 9 - MO is researching, subordinate is ready to RI-1 researching
    /// 10 - subordinate has researched part in RI-1 area; 101 - revolved
    /// 11 - commander can't find and grey points
    /// REPORT_TYPES
    struct moment {
        Robot_Scout * moving_obj;
        coordinates pos;
        int direction;
        unsigned long int time;
        int destination;
    };

    class Moving_Describer {
    private:
        std::deque<moment> move_d;
    public:
        Moving_Describer() = default;
        int addStep(moment);
        void printSteps(std::ostream & stream = std::cout);
        int makeSteps(unsigned int);
        bool isMoving(Robot_Scout *);
        unsigned int routePoint(Robot_Scout *, coordinates, int, unsigned int);
        bool onRoute(coordinates) const;
        unsigned int setDirection(Robot_Scout *, coordinates, int, int, unsigned int, int);
        bool empMd() const { return move_d.empty(); }
    };
}


#endif //ROBOTSCREATE_MOVING_DESCRIBER_H
