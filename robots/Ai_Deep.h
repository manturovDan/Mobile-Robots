#ifndef ROBOTSCREATE_AI_DEEP_H
#define ROBOTSCREATE_AI_DEEP_H

#include <map>

#include "robot.h"
#include "Managing.h"

namespace robo {
    enum ceil {
        Free,
        Obstacle,
        Interest,
        Command_Center,
        Observation_Center,
        Border,
        Not_Found
    };

    struct map_point {
        ceil iam;
        ceil top;
        ceil bottom;
        ceil right;
        ceil left;
    };

    class Ai_Deep {
    public:
        Ai_Deep() = delete;
        explicit Ai_Deep(Environment_describer *);
    private:
        std::map<coordinates, map_point> ai_dict;
    };
}


#endif //ROBOTSCREATE_AI_DEEP_H
