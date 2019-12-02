#include "Sensor.h"

namespace robo {
    Module * Sensor::copy() {
        auto nw_mm = new Sensor(radius, direction, angle,  powerConsumption, priority);
        return nw_mm;
    }
}