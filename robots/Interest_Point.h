#ifndef ROBOTSCREATE_INTEREST_POINT_H
#define ROBOTSCREATE_INTEREST_POINT_H

#include "Map_Object.h"

namespace robo {
    class Interest_Point : public Map_Object {
    public:
        Interest_Point() = delete;
        Interest_Point(coordinates pos) : Map_Object(pos) {};
        //Interest_Point * clone() const;

        std::string whoami() override;

        //~Interest_Point() override;
    };
}

#endif //ROBOTSCREATE_INTEREST_POINT_H
