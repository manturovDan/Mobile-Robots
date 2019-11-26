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
    class Module;
    class Environment_describer;

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

    ///////////////////////////////////////////////////////////////
    class Map_Object {
    protected:
        bool appeared;
        coordinates position;
        static Environment_describer *env;
    public:
        Map_Object(coordinates);
        Map_Object() : appeared(false), position({0, 0}) {}
        static void setEnv(Environment_describer *envir) { env = envir; }
        unsigned int getX() { return position.x; }
        unsigned int getY() { return position.y; }
        coordinates getPosition() { return position; }

        friend bool operator<(const Map_Object &, const Map_Object &);
        friend bool operator==(const Map_Object &left, const Map_Object &right) { return ((left.position.x == right.position.x) && (left.position.y == right.position.y)); }

        void print() { std::cout << position.x << " " << position.y <<  std::endl; }

        //virtual Map_Object * clone() const = 0; //НУЖНО ЛИ??? ASK

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
        Environment_describer() : time(0), width(0), height(0) {
            Map_Object::setEnv(this);
        };

        Environment_describer(int, int);

        void setWidth(unsigned int nval) { setWidthHeight(nval, true); }
        void setHeight(unsigned nval) { setWidthHeight(nval, false); }
        unsigned int getWidth() { return width; };
        unsigned int getHeight() { return height; };
        coordinates getObject(Map_Object &);
        Map_Object * getObject(coordinates);
        Map_Object * setObject(coordinates, Characters);
        Map_Object * setObject(unsigned int, unsigned int, int, std::vector<Module *> &, Characters, std::string &);
        Map_Object * setObject(coordinates, unsigned int, unsigned int, int, std::vector<Module *> &, Characters, std::string &);
        Quick_Navigator qTree;

        void print(std::ostream & stream = std::cout);
        ~Environment_describer() = default; // clear vector
    };


    /////////////////////////////////////////////////////////////////
    class Interest_Point : public Map_Object {
    public:
        Interest_Point() = delete;
        Interest_Point(coordinates pos) : Map_Object(pos) {};
        //Interest_Point * clone() const;

    };

    /////////////////////////////////////////////////////////////
    class Obstacle : public Map_Object {
    public:
        Obstacle() = delete;
        Obstacle(coordinates pos) : Map_Object(pos) {};
        //Obstacle * clone() const;
    };

    /////////////////////////////////////////////////////////////
    class Observation_Center : public Map_Object {
    protected:
        std::string description;
        unsigned int energyConsumption;
        int cost;
        unsigned int countPorts;
        bool appeared;
        std::vector<Module *> modules;
        void initModules(std::vector<Module *> &);
    public:
        Observation_Center() = delete;
        Observation_Center(coordinates, unsigned int, unsigned int, int, std::vector<Module *> &, std::string &);
        Observation_Center(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &);
        std::string getDescription() {  return description; }
        unsigned int getEnergyConsumption() {return energyConsumption; }
        int getCost() { return cost; }
        unsigned int getCountPorts() { return countPorts; }
        int getCountModules() { return modules.size(); }

        //Observation_Center * clone() const;
        void checkFree();
    };

    ///////////////////////////////////////////////////
    /// @bloced - true if object is moving and we cant check it in the tree
    class Robot_Scout : virtual public Observation_Center {
    protected:
        bool blocked;
        unsigned int speed;
    public:
        Robot_Scout(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &);
        unsigned int getSpeed() { return speed; }
        bool getBlocked() { return blocked; }
        int move(int);
        int turn(int);
    };

    //////////////////////////////////////////
    class Command_Center : virtual public Observation_Center {
    public:
        Command_Center(coordinates, unsigned int, unsigned int, int, std::vector<Module *> &, std::string &);
    };

    ///////////////////////////////////////////////////
    class Robot_Commander : public Robot_Scout, Command_Center {
    public:
        Robot_Commander(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &);
    };

    ///////////////////////////////////////
    ///////////////////////////////////////

    class Module {
    protected:
        Module() = delete;
        Module(int prior) : priority(prior) {}
        int priority;
        bool active;
    public:
        int getPriority();
        bool getActive();
        int setActive();

        //virtual Module * copy() = 0; // TODO for children?
    };

    class Power_Generator: public Module {
    public:
        Power_Generator(unsigned int prod) : Module() {}
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
