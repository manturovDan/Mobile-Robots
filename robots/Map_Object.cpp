#include "Map_Object.h"
#include "Environment_describer.h"

namespace robo {
    robo::Environment_describer * Map_Object::env;
    void Map_Object::setEnv(Environment_describer *envd) {
        env = envd;
    }

    Map_Object::Map_Object(coordinates coords) : appeared(true), position(coords) {
        if (coords.x > env->getWidth() - 1 || coords.y > env->getHeight() - 1)
            throw std::invalid_argument("Incorrect coordinates");

        for(robo::Env_Consistent_Iter it = env->begin(); it != env->end(); ++it) {
            if ((*it)->getPosition() == coords)
                if (!strcmp(typeid(**it).name(), "N4robo11Robot_ScoutE") || !strcmp(typeid(**it).name(), "N4robo15Robot_CommanderE"))
                    continue;
                else {
                    std::cerr << coords.x << " - " << coords.y << std::endl;
                    throw std::invalid_argument("Map object collision");
                }
        }
    }
}