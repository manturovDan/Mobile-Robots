#ifndef ROBOTSCREATE_ROBOT_H
#define ROBOTSCREATE_ROBOT_H

#include <vector>
#include <map>

#include <string>

namespace robo {
    struct map_position {
        unsigned int x;
        unsigned int y;
        int direction;
    };

    class Map_Object;

    class Environment_describer {
    private:
        unsigned int width;
        unsigned int height;
        std::vector<Map_Object *> map_obj;
    public:
        Environment_describer() = delete;
        Environment_describer(int, int);
        int setWidth(unsigned int);
        int setHeight(unsigned int);
        unsigned int getWidth();
        unsigned int getHeight();
        map_position getObject(Map_Object &);
        Map_Object * getObject(map_position);
        Map_Object * setObject(map_position, std::string, std::string description = "");
    };

    class Map_Object {
    protected:
        Map_Object() {};
        Map_Object(map_position);
        map_position position;
    public:
        map_position getPosition();
    };

    class Interest_Point : public Map_Object {
    public:
        Interest_Point() = delete;
        Interest_Point(map_position pos) : Map_Object(pos) {};
    };

    class Obstacle : public Map_Object {
    public:
        Obstacle() = delete;
        Obstacle(map_position pos) : Map_Object(pos) {};
    };

    class Module;

    class Robo_Component : public Map_Object {
    protected:
        Robo_Component() = delete;
        Robo_Component(map_position) {}

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

    class AI_Dict {

    };

    class AI {

    };
}

#endif //ROBOTSCREATE_ROBOT_H
