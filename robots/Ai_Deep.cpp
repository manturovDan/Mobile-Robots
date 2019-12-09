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
        for (auto res_re : res_res) {
            if(ai_dict.find(res_re.first) == ai_dict.end()) {
                bool bndTop = envir->isTopBoundary(res_re.first);
                bool bndRight = envir->isRightBoundary(res_re.first);

                ai_dict[res_re.first] = { res_re.second, bndTop, bndRight };
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
            "\nTop boundary:" << it.second.topBoundaty << "; Right boundary: " << it.second.rightBoundary << std::endl;
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
        md->addStep({testCom, {0, 5}, 0, 5, 0});
        md->addStep({testCom, {0, 6}, 0, 6, 0});
        md->addStep({testCom, {0, 7}, 0, 7, 3});

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

        std::vector<std::pair<Robot_Scout *, int>> nextRep;

        for (auto rep = report.begin(); rep != report.end(); ++rep) {
            if (rep->second == 1) {
                auto commer = static_cast<Robot_Commander *>(rep->first);
                auto pair = commer->getPair();
                pair->move({0, 0}, 0);
                pair->unBlock();
                nextRep.emplace_back(rep->first, 3);
            }
            else if (rep->second == 2) {
                connectResult(rep->first->look());
            }
            else if (rep->second == 3) {
                auto * commer = dynamic_cast<Robot_Commander *>(rep->first);
                std::map<coordinates, Map_Object *> resd = commer->research();
                connectResult(resd);
            }
            else if (rep->second == 4) {
                auto * commer = dynamic_cast<Robot_Commander *>(rep->first);
                if (commer->getPair() != nullptr && md->isMoving(commer->getPair()))
                    nextRep.emplace_back(rep->first, 4);
                else {
                    pairRes(commer);
                }
                //algorithm from the paper
            }

            reported(rep);
            //    throw std::invalid_argument("Unknown report");
        }

        std::remove_if(report.begin(), report.end(), [](std::pair<Robot_Scout *, int> pr){ return (pr.second == -1);} );

        for (auto it : nextRep) {
            it.first->report(it.second);
        }

    }

    bool Ai_Deep::isOpened(coordinates pos) {
        return !(ai_dict.find(pos) == ai_dict.end());
    }

    void Ai_Deep::makeReport(Robot_Scout *who, int type) {
        report.emplace_back(who, type);
    }

    void Ai_Deep::reported(std::deque<std::pair<Robot_Scout *, int>>::iterator delit) {
        (*delit).second = -1;
    }

    void Ai_Deep::pairRes(Robot_Commander * comm) {
        unsigned int ri = comm->ri();
        std::cout << "PAIR IS READYYYYYY!!!!!! - " << ri << std::endl;

        int top_cor_m, left_cor_m, bottom_cor_m, right_cor_m;
        comm->determineCorers(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m, comm->manMod()->getRadius());

        if(allOpened(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m)) {
            std::cout << "ALL_POINTS IN MO ARE OPENED" << std::endl;
        } else {
            std::cout << "ALL_POINTS IN MO ARE NOT OPENED" << std::endl;
            auto grey = findGrey(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m);
            std::cout << "GREY" << std::endl;

            std::vector<std::vector<int>> leeTab = ititLee(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m, comm->getPosition());
            /*for (auto & ly : leeTab) {
                for(int & lx : ly) {
                    std::cout << lx;
                }
                std::cout << std::endl;
            }*/
            std::cout << std::endl;
            leeComp(leeTab, left_cor_m, bottom_cor_m, comm->getPair()->getPosition());


            std::sort(grey.begin(), grey.end(), [&](coordinates const & a, coordinates const &b) { return leeTab[a.y][a.x] < leeTab[b.y][b.x]; });
            for (auto it : grey) {
                std::cout << it.x + left_cor_m << "," << it.y + bottom_cor_m << " = " << leeTab[it.y][it.x] <<  std::endl;
                std::vector<coordinates> route;
                if (leeTab[it.y][it.x] > 0) {
                    //go to to this point TODO
                    std::cout << "FULL WAY TO {" << it.x + left_cor_m << ";" << it.y + bottom_cor_m << "}" << std::endl;
                    makeRoute(leeTab, route, bottom_cor_m, left_cor_m, {it.x + left_cor_m, it.y+bottom_cor_m});
                    for (auto coord : route) {
                        std::cout << coord.x << ";" << coord.y << std::endl;
                    }
                    std::cout << "END OF THE WAY" << std::endl;

                    break;
                }
            }
        }

    }

    void Ai_Deep::makeRoute(std::vector<std::vector<int>> & leeTab, std::vector<coordinates> & route, unsigned int startX, unsigned int startY, coordinates targetPos) {
        int ceil = leeTab[targetPos.y-startY][targetPos.x-startX];
        if (ceil <= 0)
            return;

        route.clear();
        route.push_back(targetPos);
        unsigned int curX = targetPos.x;
        unsigned int curY = targetPos.y;

        while (ceil > 0) {
            if (leeTab.size() > curY-startY + 1 && leeTab[curY-startY+1][curX-startX] == ceil - 1) {
                curY++;
            }
            else if (curX != startX && leeTab[curY-startY][curX-startX-1] == ceil - 1) {
                curX--;
            }
            else if (curY != startY && leeTab[curY-startY-1][curX-startX] == ceil - 1) {
                curY--;
            }
            else if (leeTab[curY-startY].size() > curX-startX + 1 && leeTab[curY-startY][curX-startX+1] == ceil - 1) {
                curX++;
            }
            else
                throw std::invalid_argument("Invalid LEE table");

            route.push_back({curX + 1, curY});
            ceil--;
        }
    }

    bool Ai_Deep::allOpened(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor) {
        std::cout << top_cor << " " << left_cor << " " << bottom_cor << " "<< right_cor << std::endl;
        for (unsigned int h = bottom_cor; h <= top_cor; ++h) {
            for (unsigned int w = left_cor; w <= right_cor; ++w) {
                coordinates coord = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                auto p_val = ai_dict.find(coord);
                if (p_val == ai_dict.end()) {
                    return false;
                }
            }
        }

        return true;
    }

    std::vector<coordinates> Ai_Deep::findGrey(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor) {
        std::vector<coordinates> grey;

        for (unsigned int h = bottom_cor; h <= top_cor; ++h) {
            for (unsigned int w = left_cor; w <= right_cor; ++w) {
                coordinates coord = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                auto p_val = ai_dict.find(coord);

                if (p_val == ai_dict.end())
                    continue;

                if(!p_val->second.topBoundaty) {
                    if (ai_dict.find({static_cast<unsigned int>(w), static_cast<unsigned int>(h+1)}) == ai_dict.end()) {
                        grey.push_back(p_val->first);
                        continue;
                    }
                }

                if(p_val->first.x > 0) {
                    if (ai_dict.find({static_cast<unsigned int>(w-1), static_cast<unsigned int>(h)}) == ai_dict.end()) {
                        grey.push_back(p_val->first);
                        continue;
                    }
                }

                if(p_val->first.y > 0) {
                    if (ai_dict.find({static_cast<unsigned int>(w), static_cast<unsigned int>(h-1)}) == ai_dict.end()) {
                        grey.push_back(p_val->first);
                        continue;
                    }
                }

                if(!p_val->second.rightBoundary) {
                    if (ai_dict.find({static_cast<unsigned int>(w+1), static_cast<unsigned int>(h)}) == ai_dict.end()) {
                        grey.push_back(p_val->first);
                        continue;
                    }
                }

            }
        }

        return grey;
    }

    std::vector<std::vector<int>> Ai_Deep::ititLee(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor, coordinates commander) {
        std::vector<int> row (right_cor - left_cor + 1);
        std::vector<std::vector<int>> leeTab (top_cor-bottom_cor+1);

        for (unsigned int h = bottom_cor; h <= top_cor; ++h) {
            leeTab[h] = row;
            for (unsigned int w = left_cor; w <= right_cor; ++w) {
                coordinates coord = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                if(coord == commander) {
                    leeTab[h-bottom_cor][w-left_cor] = -2;
                    continue;
                }

                auto p_val = ai_dict.find(coord);
                if (p_val == ai_dict.end()) {
                    leeTab[h-bottom_cor][w-left_cor] = -2;
                    continue;
                }

                if(p_val->second.iam == nullptr || !strcmp(typeid(*p_val->second.iam).name(), "N4robo14Interest_PointE")) {
                    leeTab[h-bottom_cor][w-left_cor] = -1;
                } else {
                    leeTab[h-bottom_cor][w-left_cor] = -2;
                }
            }
        }

        return leeTab;
    }

    void Ai_Deep::leeComp(std::vector<std::vector<int>> & leeTable, unsigned int startX, unsigned int startY, coordinates start) {
        leeTable[start.y][start.x] = 0;

        int curD = 0;

        while (true) {
            bool changed = false;
            for (int i = 0; i < leeTable.size(); ++i) {
                for (int j = 0; j < leeTable[i].size(); ++j) {
                    if (leeTable[i][j] == curD) {
                        if (i != leeTable.size() - 1 && leeTable[i+1][j] == -1) {
                            leeTable[i + 1][j] = curD + 1;
                            changed = true;
                        }

                        if (j != 0 && leeTable[i][j-1] == -1) {
                            leeTable[i][j - 1] = curD + 1;
                            changed = true;
                        }

                        if (i != 0 && leeTable[i-1][j] == -1) {
                            leeTable[i - 1][j] = curD + 1;
                            changed = true;
                        }

                        if (j != leeTable[i].size()-1 && leeTable[i][j+1] == -1) {
                            leeTable[i][j + 1] = curD + 1;
                            changed = true;
                        }
                    }

                }
            }
            if(!changed)
                break;
            curD++;
        }

        for (auto & ly : leeTable) {
            for(int & lx : ly) {
                if (lx > 0)
                    std::cout << " ";
                if (lx < 10)
                    std::cout << " ";
                std::cout << lx << " ";
            }
            std::cout << std::endl;
        }
    }
}