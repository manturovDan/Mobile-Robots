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
    }
}