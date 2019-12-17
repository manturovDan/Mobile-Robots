#ifndef ROBOTSCREATE_INTEREST_POINT_H
#define ROBOTSCREATE_INTEREST_POINT_H

#include "Map_Object.h"

namespace robo {
    class Interest_Point : public Map_Object {
    public:
        Interest_Point() = delete;
        Interest_Point(coordinates pos) : Map_Object(pos) { if (pos.x == 0 && pos.y < 2) throw std::invalid_argument("Can't create Interest Point in origin"); };
        std::string whoami() override;
    };
}

#endif //ROBOTSCREATE_INTEREST_POINT_H
