#include "Map_Object.h"
#include "Environment_describer.h"

namespace robo {
    robo::Environment_describer * Map_Object::env;
    void Map_Object::setEnv(Environment_describer *envd) {
        env = envd;
    }
    /*Map_Object::Map_Object(robo::coordinates pos) : position(pos), appeared(true) {
        if (pos.x >= env->getWidth() || pos.y >= env->getHeight())
            throw std::invalid_argument("x or y is over the Map");
        //check collision
    }*/

    //int Map_Object::testEnv() {
    //    return env->testV();
    //}
}