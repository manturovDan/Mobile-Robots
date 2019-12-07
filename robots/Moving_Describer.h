#ifndef ROBOTSCREATE_MOVING_DESCRIBER_H
#define ROBOTSCREATE_MOVING_DESCRIBER_H

#include <forward_list>
#include <set>

#include "Robot_Scout.h"

namespace robo {
    struct moment {
        Robot_Scout * moving_obj;
        coordinates pos;
        int direction;
        unsigned long int time;
    };

    class Moving_Describer {
    private:
        std::forward_list<moment> move_lst;
        unsigned long int time;
    };
}


#endif //ROBOTSCREATE_MOVING_DESCRIBER_H
