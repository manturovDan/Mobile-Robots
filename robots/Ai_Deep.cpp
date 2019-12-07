#include "Ai_Deep.h"
#include "Environment_describer.h"

namespace robo {
    Ai_Deep::Ai_Deep(Environment_describer * env) : envir(env) {
        md = new Moving_Describer;
        for (Env_Consistent_Iter env_iter = envir->begin(); env_iter != envir->end(); ++env_iter) {
            bool subc = false;
            if(!strcmp(typeid(**env_iter).name(), "N4robo14Command_CenterE")) {
                add_point(*env_iter);
                auto * cc = dynamic_cast<Command_Center *>(*env_iter);
                cc->subdue();
                add_point(cc);

                for (auto cit : *cc->manMod()) {
                    add_point(cit);
                }
            } else if (!strcmp(typeid(**env_iter).name(), "N4robo15Robot_CommanderE")) {
                auto * r_com = dynamic_cast<Robot_Commander *>(*env_iter);
                if (!r_com->isManager())
                    subc = true;
                else {
                    if(r_com->chooseManModule() != 0)
                        subc = true;
                    else {
                        commanders.insert(std::pair<unsigned int, Map_Object *>(r_com->manMod()->getRadius(), *env_iter));
                    }
                }
            }

            if (subc || !strcmp(typeid(**env_iter).name(), "N4robo11Robot_ScoutE")) {
                auto * r_sc = dynamic_cast<Robot_Scout *>(*env_iter);
                scouts.insert(std::pair<unsigned int, Map_Object *>(r_sc->getMaxRadius(), *env_iter));
            }
        }

        auto com_i = commanders.rbegin();
        auto sco_i = scouts.begin();

        std::cout << "RASPR" << std::endl;

        for(; com_i != commanders.rend(); ++com_i) {
            auto *com = dynamic_cast<Robot_Commander *>(com_i->second);
            if (sco_i == scouts.end()) {
                com->setOwner(com);
            }
            else {
                auto *rob = dynamic_cast<Robot_Scout *>(sco_i->second);

                std::cout << com->getMaxRadius() << " " << com_i->first << " " << rob->getMaxRadius() << std::endl;
                if (com->getMaxRadius() < com_i->first + rob->getMaxRadius()) { //not need subordinates
                    if (!com->connectScout(rob)) {
                        sco_i++;
                    }
                }
                else {
                    com->setOwner(com);
                }
            }
        }
    }

    void Ai_Deep::add_point(Map_Object *obj) {
        ai_dict.insert(std::pair<coordinates, map_point>(obj->getPosition(), {obj, false}));
    }

    void Ai_Deep::researchMap() {
        //static researching
        for (auto dici : ai_dict) {
            if (dici.second.iam != nullptr && !strcmp(typeid(*dici.second.iam).name(), "N4robo14Command_CenterE")) {
                auto comc = dynamic_cast<Command_Center *>(dici.second.iam);
                std::map<coordinates, Map_Object *> resd = comc->research();

                ///
                /*for (auto it = resd.begin(); it != resd.end(); ++it) {
                    std::cout << it->first.x << " - " << it->first.y << " == ";
                    if (it->second == nullptr)
                        std::cout << "land";
                    else
                        std::cout << typeid(*(it->second)).name();
                    std::cout << std::endl;
                }*/

                connectResult(resd);
            }
        }

        print_d(70, 70);
    }

    void Ai_Deep::connectResult(const std::map<coordinates, Map_Object *> & res_res) {
        for (auto it = res_res.begin(); it != res_res.end(); ++it) {
            if(ai_dict.find(it->first) == ai_dict.end()) {
                ai_dict[it->first] = { it->second,false };
            }
        }
    }

    void Ai_Deep::print_d(int w, int h, std::ostream & stream) {
        stream << "DEBUG PRINTING AI DICT:\n# - unknown; L - land; P - obstacle, I - interest point, O - observation center; C - command center; R - robot commander; S - robot scout" << std::endl;
        for(unsigned int j = h-1; j >= 0 && j < h; --j) {
            for (unsigned int i = 0; i < w; ++i) {
                if (ai_dict.find({ i, j }) == ai_dict.end())
                    stream << "#";
                else {
                    Map_Object * co = ai_dict[{ i, j }].iam;
                    if (co == nullptr)
                        stream << "L";
                    else {
                        if (!strcmp(typeid(*co).name(), "N4robo14Command_CenterE"))
                            stream << "C";
                        else if (!strcmp(typeid(*co).name(), "N4robo18Observation_CenterE"))
                            stream << "O";
                        else if (!strcmp(typeid(*co).name(), "N4robo14Interest_PointE"))
                            stream << "I";
                        else if (!strcmp(typeid(*co).name(), "N4robo8ObstacleE"))
                            stream << "P";
                        else// if (!strcmp(typeid(*co).name(), "N4robo8ObstacleE"))
                            stream << "A";
                    }
                }
            }
            stream << std::endl;
        }

        stream << "Robot_Commanders: " << std::endl;
        for (auto & com : commanders) {
            stream << dynamic_cast<Robot_Commander *>(com.second)->getDescription() << std::endl;
        }

        stream << std::endl << "Scouts:" << std::endl;
        for (auto & sc : scouts) {
            std::cout << dynamic_cast<Robot_Scout *>(sc.second)->getDescription() << std::endl;
        }

    }

    void Ai_Deep::print(std::ostream & stream) {
        std::cout << "\n\n--------------------------------------\n Printing AI Storage\n--------------------------------------\n" << std::endl;
        for (auto it : ai_dict) {
            std::string who = it.second.iam == nullptr ? "LAND" : it.second.iam->whoami();
            std::cout << "KEY: { " << it.first.x << "; " << it.first.y << " }\n" << who <<
            "\nBoundary:" << it.second.isBoundary << std::endl;
        }
    }

    void Ai_Deep::run() {
        researchMap();
    }

    void Ai_Deep::testMove() {
        Robot_Commander * testCom = dynamic_cast<Robot_Commander *>(commanders.rbegin()->second);

        testCom->unBlock();
    }

    void Ai_Deep::testNext() {
        Robot_Commander * testCom = dynamic_cast<Robot_Commander *>(commanders.rbegin()->second);
        md->addStep({testCom, {0, 1}, 0, 1, 0});
        md->addStep({testCom, {0, 2}, 0, 2, 0});
        md->addStep({testCom, {0, 3}, 0, 3, 0});
        md->addStep({testCom, {0, 4}, 0, 4, 0});
        md->addStep({testCom, {0, 5}, 0, 5, 1});

        md->printSteps();
    }

    /// returns 1 if all commanders are researching, 0 - some commanders are rest, 2 - start points are busy
    int Ai_Deep::startCommander() {
        if(envir->checkMobOnPoint({0, 0}) != nullptr || envir->checkMobOnPoint({0, 1}) != nullptr)
            return 2;

        for (auto & com_it : commanders) {
            auto * com = dynamic_cast<Robot_Commander *>(com_it.second);

            if (com->getBlocked()) {
                com->move({0, 0}, 0);
                com->unBlock();
                if (com->manMod()->subord_count() > 0)
                    md->addStep({com, {0, 1}, 0, envir->getTime()+1, 1});
                return 0;
            }
        }

        return 1;
    }

    void Ai_Deep::nextComp() {
        std::cout << startCommander() << std::endl;
        md->printSteps();
    }
}