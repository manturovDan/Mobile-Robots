#include "Interest_Point.h"

namespace robo {
    std::string Interest_Point::whoami() {
        std::stringstream ss;
        ss << "Interest Point {" << position.x << ", " << position.y << "}" << std::endl;
        return ss.str();
    }
}