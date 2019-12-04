#include "Power_Generator.h"

namespace robo {
    Module * Power_Generator::copy() {
        auto nw_mm = new Power_Generator(priority, energyProduction);
        return nw_mm;
    }

    std::string Power_Generator::whoami() {
        std::stringstream ss;
        ss << "Power Generator energyProduction = " << energyProduction << " priority = " << priority << " active = " << active;
        return ss.str();
    }
}