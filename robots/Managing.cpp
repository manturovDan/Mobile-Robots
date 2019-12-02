#include "Managing.h"

namespace robo {
    Module * Managing::copy() {
        auto nw_mm = new Managing(radius, powerConsumption, priority, subs_count);
        return nw_mm;
    }
}