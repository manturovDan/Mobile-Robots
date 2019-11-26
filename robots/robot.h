#ifndef ROBOTSCREATE_ROBOT_H
#define ROBOTSCREATE_ROBOT_H

#include <vector>
#include <string>
#include <map>
#include <cstring>

namespace robo {
    struct coordinates {
        unsigned int x;
        unsigned int y;
    };

    enum Characters {
        Obstacle_t,
        Interest_t,
        Command_Center_t,
        Robot_Commander_t,
        Observation_Center_t,
        Robot_Scout_t
    };

    class Map_Object;

    /////////////////////////////////////////////////////
    class Quick_Navigator {
    private:
        std::multimap<robo::coordinates, robo::Map_Object *> objectTree;
    public:
        Quick_Navigator() = default;
        //Map_Object * check(coordinates position) { return (*objectTree.find(position)).second; };
        void add(Map_Object *);
        int replace(coordinates);
    };

    /////////////////////////////////////////////////////////////////
    class Environment_describer {
    private:
        unsigned int width;
        unsigned int height;
        unsigned int time;
        std::vector<Map_Object *> map_obj;

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
        Quick_Navigator qTree;

        void print(std::ostream & stream = std::cout);
        ~Environment_describer() = default; // clear vector
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
        unsigned int getX() { return position.x; }
        unsigned int getY() { return position.y; }
        coordinates getPosition() { return position; }

        friend bool operator<(const Map_Object &, const Map_Object &);
        friend bool operator==(const Map_Object &left, const Map_Object &right) { return ((left.position.x == right.position.x) && (left.position.y == right.position.y)); }

        void print() { std::cout << position.x << " " << position.y <<  std::endl; }

        //virtual Map_Object * clone() const = 0; //НУЖНО ЛИ??? ASK

        virtual void setGenerator(unsigned int prod) = 0;
    };


    /////////////////////////////////////////////////////////////////
    class Interest_Point : public Map_Object {
    public:
        Interest_Point() = delete;
        Interest_Point(coordinates pos) : Map_Object(pos) {};
        Interest_Point * clone() const;

        void setGenerator(unsigned int prod) { throw std::invalid_argument("Incorrect object for generator"); } // IS IT GOOD?
    };

    class Obstacle : public Map_Object {
    public:
        Obstacle() = delete;
        Obstacle(coordinates pos) : Map_Object(pos) {};
        Obstacle * clone() const;
        void setGenerator(unsigned int prod) { throw std::invalid_argument("Incorrect object for generator"); } // IS IT GOOD?
    };

    class Module;

    class Observation_Center : public Map_Object {
    protected:
        Observation_Center();
        coordinates position;
        std::string description;
        int energyConsumption;
        int cost;
        int countPorts;
        bool appeared;
        std::vector<Module *> modules;
    public:
        Observation_Center(coordinates pos) : Map_Object(pos) {}
        std::string getDescription();
        int getEnergyConsumption();
        int getCost();
        int getCountPorts();
        int getCountModules() { return modules.size(); }
        Observation_Center * clone() const;
        void setGenerator(unsigned int);
    };

    class Robot_Scout : virtual public Observation_Center {
    public:
        Robot_Scout(coordinates pos) : Observation_Center(pos) { }
        int getSpeed();
        int move(int);
        int turn(int);
    };

    class Command_Center : virtual public Observation_Center {
    public:
        Command_Center(coordinates pos) : Observation_Center(pos) {}
    };

    class Robot_Commander : public Robot_Scout, Command_Center {
    public:
        Robot_Commander(coordinates pos) : Robot_Scout(pos), Command_Center(pos), Observation_Center(pos) {}
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

    class Power_Generator: public Module {
    public:
        Power_Generator() : Module() {}
    protected:
        int energyProduction;
    };

    class Energy_Consumer {
    protected:
        Energy_Consumer();
        int powerConsumption;
    };

    class Managing : public Energy_Consumer {
    public:
        Managing();
    protected:
        //std::vector<Robo_Component *> subordinate;
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
