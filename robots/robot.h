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

    inline bool operator <(coordinates left, coordinates right) {
        if (left.x < right.x)
            return true;
        else if (left.x == right.x) {
            if (left.y < right.y)
                return true;
        }

        return false;
    }

    inline bool operator == (coordinates left, coordinates right) {
        return ((left.x == right.x) && (left.y == right.y));
    }


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

}

#endif //ROBOTSCREATE_ROBOT_H
