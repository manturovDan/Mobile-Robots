#ifndef ROBOTSCREATE_ROBOT_H
#define ROBOTSCREATE_ROBOT_H

#include <vector>
#include <string>
#include <map>

namespace robo {
    struct coordinates {
        unsigned int x;
        unsigned int y;
    };

    enum Characters {
        Obstacle_t,
        Interest_t
    };

    class Map_Object;


    /////////////////////////////////////////////////////////////////
    class Environment_describer {
    private:
        unsigned int width;
        unsigned int height;
        unsigned int time;
        std::vector<Map_Object> map_obj;

        /// @param bool coord : x - true, y - false
        int setWidthHeight(int, bool);
    public:
        Environment_describer() : time(0), width(0), height(0) {};
        Environment_describer(int, int);

        void setWidth(unsigned int nval) { setWidthHeight(nval, true); }
        void setHeight(unsigned nval) { setWidthHeight(nval, false); }
        unsigned int getWidth() { return width; };
        unsigned int getHeight() { return height; };
        coordinates getObject(Map_Object &);
        Map_Object * getObject(coordinates);
        Map_Object * setObject(coordinates, Characters, std::string description = "undefined");
    };


    ///////////////////////////////////////////////////////////////
    class Map_Object {
    protected:
        Map_Object() = delete;
        bool appeared;
        bool blocked;
        coordinates position;
    public:
        Map_Object(coordinates);
        unsigned int getX() { return position.x; };
        unsigned int getY() { return position.y; };

        friend bool operator<(const Map_Object &, const Map_Object &);
        friend bool operator==(const Map_Object &left, const Map_Object &right) { return ((left.position.x == right.position.x) && (left.position.y == right.position.y)); }
    };

    class Interest_Point : public Map_Object {
    public:
        Interest_Point() = delete;
        Interest_Point(coordinates pos) : Map_Object(pos) {};
    };

    class Obstacle : public Map_Object {
    public:
        Obstacle() = delete;
        Obstacle(coordinates pos) : Map_Object(pos) {};
    };

    class Module;

    class Robo_Component : public Map_Object {
    protected:
        Robo_Component() = delete;
        Robo_Component(coordinates);

        coordinates position;
        std::string description;
        int energyConsumption;
        int cost;
        int countPorts;
        bool appeared;
        std::vector<Module *> modules;
    public:
        std::string getDescription();
        int getEnergyConsumption();
        int getCost();
        int getCountPorts();
        coordinates getPosition();
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

    class QuickNavigator {
    private:
        std::multimap<robo::coordinates, robo::Map_Object *> objectTree;
    public:
        Map_Object * check(coordinates);
        int add(Map_Object *);
        int replace(coordinates);
    };

    class AI_Dict {

    };

    class AI {

    };
}

#endif //ROBOTSCREATE_ROBOT_H
