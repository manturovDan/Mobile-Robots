#include "Command_Center.h"
#include "Robot_Commander.h"
#include "Environment_describer.h"

namespace robo {
    Robot_Commander::Robot_Commander(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods, std::string & desc)
    : Command_Center(ports, consumption, price, mods, desc),
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

    Robot_Scout * Robot_Commander::getPair() const {
        for(auto it : *manMod()) {
            if (it->getOwner() == this && !strcmp(typeid((*it)).name(), "N4robo11Robot_ScoutE")) {
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

        if (getPair() != nullptr) {
            unsigned int max_rad_s = getPair()->getMaxRadius();
            int top_cor_s, left_cor_s, bottom_cor_s, right_cor_s;
            getPair()->determineCorers(top_cor_s, left_cor_s, bottom_cor_s, right_cor_s, max_rad_s);
            if (manMod()->unknownSquare(top_cor_s, top_cor_s, top_cor_s, top_cor_s)) {
                look_res = getPair()->look();
                full_look_res.insert(look_res.begin(), look_res.end());
            }

            if (manMod()->unknownSquare(top_cor_s, left_cor_s, bottom_cor_s, right_cor_s)) {
                manMod()->addStep(getPair(), getPair()->getPosition(), (getPair()->getDirection() + 1) % 4, env->getTime()+1, 2);
                manMod()->addStep(getPair(), getPair()->getPosition(), (getPair()->getDirection() + 2) % 4, env->getTime()+2, 2);
                manMod()->addStep(getPair(), getPair()->getPosition(), (getPair()->getDirection() + 3) % 4, env->getTime()+3, 2);
                manMod()->addStep(getPair(), getPair()->getPosition(), getPair()->getDirection(), env->getTime()+4, 0);
            }
        }


        if (manMod()->unknownSquare(top_cor, left_cor, bottom_cor, right_cor)) {
            manMod()->addStep(this, position, (direction + 1) % 4, env->getTime()+1, 2);
            manMod()->addStep(this, position, (direction + 2) % 4, env->getTime()+2, 2);
            manMod()->addStep(this, position, (direction + 3) % 4, env->getTime()+3, 2);
        }

        manMod()->addStep(this, position, direction, env->getTime()+4, 4);

        return full_look_res;
    }

    unsigned int Robot_Commander::ri() const {
        if (getPair() != nullptr)
            return manMod()->getRadius() + getPair()->getMaxRadius();
        return manMod()->getRadius();
    }
}