#ifndef ROBOTSCREATE_DISPLAY_H
#define ROBOTSCREATE_DISPLAY_H

#include <SFML/Graphics.hpp>

#include "Environment_describer.h"

namespace dispr {
    class Display {
    private:
        robo::Environment_describer * env;
    public:
        Display() = delete;
        Display(robo::Environment_describer *);



    };
}

#endif //ROBOTSCREATE_DISPLAY_H
