#ifndef ROBOTSCREATE_ROBOT_H
#define ROBOTSCREATE_ROBOT_H

#include <vector>

#include <string>

namespace robo {
    struct map_position {
        unsigned int x;
        unsigned int y;
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
    protected:
        Map_Object() {}
    public:
        map_position getPosition();
    };

    class Obstacle : public Map_Object {
    public:
        Obstacle() {}
    };

    class Interest_Point : public Map_Object {
    public:
        Interest_Point() {}
    };

    class Module;

    class Robo_Component : public Map_Object {
    protected:
        Robo_Component() {}

        map_position position;
        std::string description;
        int energyConsumption;
        int cost;
        int countPorts;
        std::vector<Module *> modules;
    public:
        std::string getDescription();
        int getEnergyConsumption();
        int getCost();
        int getCountPorts();
        map_position getPosition();
    };

    class Mobile : Robo_Component {
    protected:
        Mobile ();
        int speed;
    public:
        int getSpeed();
        int move(int);
        int turn(int);
    };

    class Manager : public Robo_Component {
    protected:
        Manager ();
    };

    class Robot_Scout : public Mobile {
    public:
        Robot_Scout();
    };

    class Robot_Commander : public Robot_Scout, public Manager { //make virtual
    public:
        Robot_Commander();
    };

    class Observation_Center : public Robo_Component {
    public:
        Observation_Center();
    };

    class Command_Center : public Observation_Center, public Manager {
        Command_Center();
    };

    class Module {
    protected:
        Module();
        int priority;
        bool active;
    public:
        int getPriority();
        bool getActive();
        int setActive();
    };

    class Energy_Consumer {
    protected:
        Energy_Consumer();
        int powerConsumption;
    };

    class Power_Generator {
    public:
        Power_Generator();
    protected:
        int energyProduction;
    };

    class Managing : public Energy_Consumer {
    public:
        Managing();
    protected:
        std::vector<Robo_Component *> subordinate;
    };

    class Sensor : public Energy_Consumer {
    public:
        Sensor();
    protected:
        int radius;
        int direction;
        int angle;

    };
}

#endif //ROBOTSCREATE_ROBOT_H
