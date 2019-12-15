#include "Sensor.h"

namespace robo {
    Module * Sensor::copy() {
        auto nw_mm = new Sensor(radius, direction, angle,  powerConsumption, priority);
        return nw_mm;
    }

    std::string Sensor::whoami() {
        std::stringstream ss;
        ss << "\tSensor radius = " << radius << " direction = " << direction << " powerConsumption = " << powerConsumption << " priority = " << priority << " active = " << active;
        return ss.str();
    }

    Sensor::Sensor(unsigned int rad, unsigned int dir, unsigned int ang, unsigned int consumption,
                   unsigned int priority) : radius(rad), direction(dir), angle(ang), Energy_Consumer(consumption, priority, true) {
        if (angle == 2) {
            direction = 0;
        }
    }
}