#ifndef ROBOTSCREATE_OBSERVATION_CENTER_H
#define ROBOTSCREATE_OBSERVATION_CENTER_H

#include <vector>
#include <string>

#include "Map_Object.h"
#include "Module.h"

namespace robo {
    class Observation_Center : public Map_Object {
    protected:
        std::string description;
        unsigned int energyConsumption;
        int cost;
        unsigned int countPorts;
        bool appeared;
        std::vector<Module *> modules;

        void initModules(const std::vector<Module *> &);

    public:
        Observation_Center() = delete;

        Observation_Center(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &, coordinates pos = {0, 0});

        //Observation_Center(unsigned int, unsigned int, int, std::vector<Module *> &, std::string &);
        std::string getDescription() { return description; }

        unsigned int getEnergyConsumption() { return energyConsumption; }

        int getCost() { return cost; }

        unsigned int getCountPorts() { return countPorts; }

        int getCountModules() { return modules.size(); }

        //Observation_Center * clone() const;
        void checkFree();
    };
}

#endif //ROBOTSCREATE_OBSERVATION_CENTER_H
