#ifndef ROBOTSCREATE_OBSTACLE_H
#define ROBOTSCREATE_OBSTACLE_H

#include "Map_Object.h"

namespace robo {
    class Obstacle : public Map_Object {
    public:
        Obstacle() = delete;

        Obstacle(coordinates pos) : Map_Object(pos) { if (pos.x == 0 && pos.y < 2) throw std::invalid_argument("Can't create Obstacle in origin"); };
        //Obstacle * clone() const;
        std::string whoami() override ;

    };
}

#endif //ROBOTSCREATE_OBSTACLE_H
