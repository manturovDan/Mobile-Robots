#ifndef ROBOTSCREATE_SENSOR_H
#define ROBOTSCREATE_SENSOR_H

#include <sstream>

#include "Environment_describer.h"
#include "Energy_Consumer.h"

namespace robo {
    class Sensor : public Energy_Consumer {
    public:
        Sensor() = delete;
        Sensor(unsigned int rad, unsigned int dir, unsigned int ang, unsigned int consumption, unsigned int priority) :
                radius(rad), direction(dir), angle(ang), Energy_Consumer(consumption, priority, true) { if (angle == 2) { direction = 0; } }
        Module * copy() override;
        unsigned int getRadius() override { return radius; }
        unsigned int getDirection(int dir = 0) { return (dir+direction) % 4; }
        unsigned int getAngle() { return angle; }

        std::string whoami() override;
        ~Sensor() override = default;
    protected:
        unsigned int radius;
        unsigned int direction;
        unsigned int angle;

    };
}

#endif //ROBOTSCREATE_SENSOR_H
