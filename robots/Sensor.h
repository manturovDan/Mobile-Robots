#ifndef ROBOTSCREATE_SENSOR_H
#define ROBOTSCREATE_SENSOR_H

#include "Environment_describer.h"
#include "Energy_Consumer.h"

namespace robo {
    class Sensor : public Energy_Consumer {
    public:
        Sensor() = delete;
        Sensor(unsigned int rad, unsigned int dir, unsigned int ang, unsigned int consumption, unsigned int priority) :
                radius(rad), direction(dir), angle(ang), Energy_Consumer(consumption, priority, false) {  }
    protected:
        unsigned int radius;
        unsigned int direction;
        unsigned int angle;

    };
}

#endif //ROBOTSCREATE_SENSOR_H
