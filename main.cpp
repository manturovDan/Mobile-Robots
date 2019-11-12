#include <iostream>

#include "robots/robot.h"

int main()
{
    robo::Environment_describer env(100, 100);
    robo::Map_Object *obs1 = env.setObject({10, 10, 1}, "Obstacle");

}