#ifndef ROBOTSCREATE_MOVING_DESCRIBER_H
#define ROBOTSCREATE_MOVING_DESCRIBER_H

#include <deque>

#include "Robot_Scout.h"

namespace robo {
    /// destination == 0 - nothing to do, moving is continue; 1 - commander has arrived to 0,1 - need a subordinate; 2 - scout has arrived to task point; 3 - commander has arrived to new point;
    struct moment {
        Robot_Scout * moving_obj;
        coordinates pos;
        int direction;
        unsigned long int time;
        bool destination;
    };

    class Moving_Describer {
    private:
        std::deque<moment> move_d;
    public:
        Moving_Describer() = default;
        int addStep(moment);
        void printSteps(std::ostream & stream = std::cout);
        void makeSteps(unsigned int);
    };
}


#endif //ROBOTSCREATE_MOVING_DESCRIBER_H
