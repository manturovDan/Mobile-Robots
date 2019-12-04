#include "Sensor.h"

namespace robo {
    Module * Sensor::copy() {
        auto nw_mm = new Sensor(radius, direction, angle,  powerConsumption, priority);
        return nw_mm;
    }

    std::string Sensor::whoami() {
        std::stringstream ss;
        ss << "Sensor radius = " << radius << " direction = " << direction << " powerConsumption = " << powerConsumption << " priority = " << priority << " active = " << active;
        return ss.str();
    }
}