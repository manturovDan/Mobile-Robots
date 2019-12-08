#include "Robot_Scout.h"
#include "Observation_Center.h"
#include "Sensor.h"

namespace robo {
    Robot_Scout::Robot_Scout(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods,
            std::string & desc) : blocked(true), direction(0),
            Observation_Center(ports, consumption, price, mods, desc) {}

    std::string Robot_Scout::whoami() {
        std::stringstream ss;
        std::string host = owner != nullptr ? owner->getDescription() : "none";

        ss << "Object : Robot_Scout: {" << position.x << ", " << position.y << "}\nDesc: '" << description << "';\n"
                                     "Consumption: " << energyConsumption << ";\nCost: " << cost << ";\n"
                                      "PortsCount: " << countPorts << ";\nAppeared: " << appeared << ";\n"
                                      "Blocked: " << blocked << "\n"
                                      "Owner = " << host << std::endl;
        ss << "Modules:\n" << myModules() << std::endl;
        return ss.str();
    }

    void Robot_Scout::move(coordinates pos, int dir) {
        position.x = pos.x;
        position.y = pos.y;

        direction = dir;
    }

    void Robot_Scout::report(int type) {
        dynamic_cast<Command_Center *>(owner)->comReport(this, type);
    }

    //bool check all opened if square
    /*
    std::map<coordinates, Map_Object *> Robot_Scout::look() {
        unsigned int max_rad = getMaxRadius();
        int top_cor, left_cor, bottom_cor, right_cor;
        determineCorers(top_cor, left_cor, bottom_cor, right_cor, max_rad);

        for (int h = top_cor; h >= bottom_cor; --h) {
            for (int w = left_cor; w <= right_cor; ++w) {
                if ()

            }
            std::cout << std::endl;
        }

        std::map<coordinates, Map_Object *> one_view;
        one_view = Observation_Center::look();


    }*/
}