#ifndef ROBOTSCREATE_ROBOT_H
#define ROBOTSCREATE_ROBOT_H

namespace robo {
    struct map_position {
        unsigned int x;
        unsigned int y;
        unsigned int x_size;
        unsigned int y_size;
        int direction;
    };

    class Environment_describer {
    private:
        unsigned int width;
        unsigned int height;
        //TODO matrix of map_objects
    public:
        //TODO constructors
        int setWidth(unsigned int);
        int setHeight(unsigned int);
        unsigned int getWidth();
        unsigned int getHeight();
        //TODO setObject
        //TODO getObject
    };

    class Map_Object {
    private:
        map_position position;
    public:
        map_position getPosition();
    };

    class Obstacle : public Map_Object {};

    class Interest_Point : public Map_Object {};

    class Robo_Component : public Map_Object {};
}

#endif //ROBOTSCREATE_ROBOT_H
