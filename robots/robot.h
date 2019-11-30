#ifndef ROBOTSCREATE_ROBOT_H
#define ROBOTSCREATE_ROBOT_H

#include <vector>
#include <string>
#include <map>
#include <cstring>

namespace robo {
    struct coordinates {
        unsigned int x;
        unsigned int y;
    };

    enum Characters {
        Obstacle_t,
        Interest_t,
        Command_Center_t,
        Robot_Commander_t,
        Observation_Center_t,
        Robot_Scout_t
    };

    /////////////////////////////////////////////////////
    /*class Quick_Navigator {
    private:
        std::multimap<robo::coordinates, robo::Map_Object *> objectTree;
    public:
        Quick_Navigator() = default;
        //Map_Object * check(coordinates position) { return (*objectTree.find(position)).second; };
        void add(Map_Object *);
        int replace(coordinates);
    };*/

    class AI_Dict {

    };

    class AI {

    };
}

#endif //ROBOTSCREATE_ROBOT_H
