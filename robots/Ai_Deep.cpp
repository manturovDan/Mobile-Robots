#include "Ai_Deep.h"
#include "Environment_describer.h"

namespace robo {
    Ai_Deep::Ai_Deep(Environment_describer * env) {
        for (Env_Consistent_Iter env_iter = env->begin(); env_iter != env->end(); ++env_iter) {
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
                if (r_com->isManager())
                    subc = true;
                else {
                    if(r_com->chooseManModule())
                        subc = true;
                    else {
                        managers.insert(std::pair<unsigned int, Map_Object *>(r_com->manMod()->getRadius(), *env_iter));
                    }
                }
            }

            if (subc || !strcmp(typeid(**env_iter).name(), "N4robo11Robot_ScoutE")) {
                auto * r_sc = dynamic_cast<Robot_Scout *>(*env_iter);
                managers.insert(std::pair<unsigned int, Map_Object *>(r_sc->getMaxRadius(), *env_iter));
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
    }

    void Ai_Deep::print(std::ostream & stream) {
        std::cout << "\n\n--------------------------------------\n Printing AI Storage\n--------------------------------------\n" << std::endl;
        for (auto it : ai_dict) {
            std::string who = it.second.iam == nullptr ? "LAND" : it.second.iam->whoami();
            std::cout << "KEY: { " << it.first.x << "; " << it.first.y << " }\n" << who <<
            "\nBoundary:" << it.second.isBoundary << std::endl;
        }
    }
}