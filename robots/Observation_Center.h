#ifndef ROBOTSCREATE_OBSERVATION_CENTER_H
#define ROBOTSCREATE_OBSERVATION_CENTER_H

#include <vector>
#include <map>

#include "Map_Object.h"
#include "Module.h"
#include "robot.h"

namespace robo {
    class Sensor;
    class Observation_Center : public Map_Object {
    protected:
        std::string description;
        unsigned int energyConsumption;
        int cost;
        unsigned int countPorts;
        bool appeared;
        std::vector<Module *> modules;
        void initModules(const std::vector<Module *> &);
        Observation_Center * owner;

    public:
        Observation_Center() = delete;
        Observation_Center(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &, coordinates pos = {0, 2});
        std::string getDescription() const { return description; }
        unsigned int getEnergyConsumption() const { return energyConsumption; }
        int getCost() const { return cost; }
        unsigned int getCountPorts() { return countPorts; }
        int getCountModules() const { return modules.size(); }
        std::string whoami() override;
        std::string myModules();
        std::map<coordinates, Map_Object *> look();
        void determineCorers(int &, int &, int &, int &, unsigned int) const;
        static void determineCorers(int &, int &, int &, int &, unsigned int, coordinates);
        void setOwner(Map_Object *);
        Map_Object * getOwner() const { return owner; }
        unsigned int getMaxRadius() const;
        virtual int getDirection() const { return 0; }
        ~Observation_Center() override;
    };
}

#endif //ROBOTSCREATE_OBSERVATION_CENTER_H
