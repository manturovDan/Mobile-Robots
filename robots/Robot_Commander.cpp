#include "Command_Center.h"
#include "Robot_Commander.h"

namespace robo {
    Robot_Commander::Robot_Commander(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods, std::string & desc)
    : Command_Center(ports, consumption, price, mods, desc, {0, 0}),
    Robot_Scout(ports, consumption, price, mods, desc), Observation_Center(ports, consumption, price, mods, desc) {}

    std::string Robot_Commander::whoami() {
        std::stringstream ss;
        std::string host = owner != nullptr ? owner->getDescription() : "none";

        ss << "Object : Robot_Commander: {" << position.x << ", " << position.y << "}\nDesc: '" << description << "';\n"
                                         "Consumption: " << energyConsumption << ";\nCost: " << cost << ";\n"
                                         "PortsCount: " << countPorts << ";\nAppeared: " << appeared << ";\n"
                                         "Blocked: " << blocked << "\n"
                                         "Owner = " << host << "\nReal Manager: " << real_manager << std::endl;
        ss << "Modules:\n" << myModules() << std::endl;
        return ss.str();
    }

    int Robot_Commander::connectScout(Robot_Scout * sco) {
        if (sco->getOwner() == nullptr) {
            if (matchMan->addSubord(sco)) {
                return 1;
            }

            sco->setOwner(this);
            setOwner(this);
            return 0;

        }
        return 1;
    }

    Robot_Scout * Robot_Commander::getPair() {
        for(auto it : *manMod()) {
            if (it->getOwner() == this) {
                return dynamic_cast<Robot_Scout *>(it);
            }
        }

        return nullptr;
    }

    std::map<coordinates, Map_Object *> Robot_Commander::research() {
        std::map<coordinates, Map_Object *> full_look_res;
        std::map<coordinates, Map_Object *> look_res;


        unsigned int max_rad = getMaxRadius();
        int top_cor, left_cor, bottom_cor, right_cor;
        determineCorers(top_cor, left_cor, bottom_cor, right_cor, max_rad);

        if (manMod()->unknownSquare(top_cor, left_cor, bottom_cor, right_cor)) {
            look_res = look();
            full_look_res.insert(look_res.begin(), look_res.end());
        }

        unsigned int max_rad_s = getPair()->getMaxRadius();
        int top_cor_s, left_cor_s, bottom_cor_s, right_cor_s;
        getPair()->determineCorers(top_cor_s, left_cor_s, bottom_cor_s, right_cor_s, max_rad_s);
        if (manMod()->unknownSquare(top_cor, left_cor, bottom_cor, right_cor)) {
            look_res = getPair()->look();
            full_look_res.insert(look_res.begin(), look_res.end());
        }

        //std::map<coordinates, Map_Object *> look_res = look();

        //full_look_res.insert(look_res.begin(), look_res.end());

        return full_look_res;
    }
}