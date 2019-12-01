#include "Obstacle.h"

namespace robo {
    std::string Obstacle::whoami() {
        std::stringstream ss;
        ss << "Obstacle {" << position.x << ", " << position.y << "}" << std::endl;
        return ss.str();
    }
}