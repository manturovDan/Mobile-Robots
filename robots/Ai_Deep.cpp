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
                if (r_sc->getMaxRadius() > 0)
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
        bool topB = false;
        bool rightB = false;
        if (obj->getY() == envir->getHeight()-1)
            topB = true;
        if (obj->getX() == envir->getWidth() - 1)
            rightB = true;

        ai_dict.insert(std::pair<coordinates, map_point>(obj->getPosition(), {obj, topB, rightB}));
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
                else
                    md->addStep({com, {0, 0}, 0, envir->getTime()+1, 1});
                return 0;
            }
        }

        return 1;
    }

    void Ai_Deep::nextComp() {
        startCommander();
        md->printSteps();

        std::vector<std::pair<Robot_Scout *, int>> nextRep;

        for (auto rep = report.begin(); rep != report.end(); ++rep) {
            std::cout << "REP " << rep->second << " - " << rep->first->getDescription() << std::endl;
            if (rep->second == 1) {
                auto commer = static_cast<Robot_Commander *>(rep->first);
                auto pair = commer->getPair();
                if (pair != nullptr) {
                    pair->move({0, 0}, 0);
                    pair->unBlock();
                }
                nextRep.emplace_back(rep->first, 3);

                int top_cor_ri, left_cor_ri, bottom_cor_ri, right_cor_ri;
                unsigned int pair_rad;

                if (commer->getPair() != nullptr)
                    pair_rad = dynamic_cast<Robot_Scout *>(commer->getPair())->getMaxRadius();
                else
                    pair_rad = commer->getMaxRadius();

                commer->determineCorers(top_cor_ri, left_cor_ri, bottom_cor_ri, right_cor_ri, commer->manMod()->getRadius() + pair_rad);
                addArea(top_cor_ri, left_cor_ri, bottom_cor_ri, right_cor_ri);
            }
            else if (rep->second == 2) {
                //maybe subdue lonely observation center
                connectResult(rep->first->look());
            }
            else if (rep->second == 3) {
                Robot_Commander * commer;
                commer = dynamic_cast<Robot_Commander *>(rep->first->getOwner());
                std::map<coordinates, Map_Object *> resd = commer->research();
                connectResult(resd);
            }
            else if (rep->second == 4) {
                auto * commer = dynamic_cast<Robot_Commander *>(rep->first);
                addBlockedPoint(commer->getPosition());
                if(commer->getPair() != nullptr)
                    addBlockedPoint(commer->getPair()->getPosition());

                if (commer->getPair() != nullptr) {
                    if (md->isMoving(commer->getPair()))
                        nextRep.emplace_back(rep->first, 4);
                    else {
                        if (pairRes(commer)) {
                            makeReport(commer->getPair(), 5);
                        } else
                            makeReport(commer->getPair(), 9);
                    }
                }
                else
                    nextRep.emplace_back(commer, 8);
            } else if (rep->second == 5) {
                connectResult(rep->first->look());
                auto * subd = dynamic_cast<Robot_Scout *>(rep->first);
                revolve(subd, 55);
            } else if (rep->second == 55) {
                auto * subd = dynamic_cast<Robot_Scout *>(rep->first);
                if(pairRes(dynamic_cast<Robot_Commander *>(subd->getOwner()))) {
                    makeReport(subd, 9);//6 - back to chief
                }
            } else if (rep->second == 6) {
                if(backToChief(dynamic_cast<Robot_Commander *>(rep->first->getOwner())))
                    makeReport(rep->first, 7);
            } else if (rep->second == 7) {
                if(md->setDirection(rep->first, rep->first->getPosition(), dynamic_cast<Robot_Commander *>(rep->first->getOwner())->getDirection(), rep->first->getDirection(), envir->getTime()+1, 8) == envir->getTime()+1)
                    makeReport(rep->first, 8);
            } else if (rep->second == 8) {
                auto * comm = dynamic_cast<Robot_Commander *>(rep->first->getOwner());
                int top_cor_ri, left_cor_ri, bottom_cor_ri, right_cor_ri;
                unsigned int pair_rad = rep->first->getMaxRadius();
                comm->determineCorers(top_cor_ri, left_cor_ri, bottom_cor_ri, right_cor_ri, comm->manMod()->getRadius() + pair_rad);
                deleteArea(top_cor_ri, left_cor_ri, bottom_cor_ri, right_cor_ri);
                trainNext(comm);
            } else if (rep->second == 9) {
                if(riRes(dynamic_cast<Robot_Commander *>(rep->first->getOwner()))) {
                    auto * subd = dynamic_cast<Robot_Scout *>(rep->first);
                    makeReport(subd, 6);
                }
            } else if (rep->second == 10) {
                connectResult(rep->first->look());
                auto * subd = dynamic_cast<Robot_Scout *>(rep->first);
                revolve(subd, 101);

            } else if (rep->second == 101) { //101
                auto * subd = dynamic_cast<Robot_Scout *>(rep->first);
                if (riRes(dynamic_cast<Robot_Commander *>(rep->first->getOwner()))) {
                    //makeReport(subd, 10);
                    makeReport(subd, 6);
                }
                else {
                    makeReport(subd, 1011);
                }
            } else if (rep->second == 11) {
                auto * comm = dynamic_cast<Robot_Commander *>(rep->first->getOwner());
                //check the end there
                trainNext(comm);
            }

            reported(rep);
            //    throw std::invalid_argument("Unknown report");
        }

        report.erase(std::remove_if(report.begin(), report.end(), [](std::pair<Robot_Scout *, int> pr){ return (pr.second == -1);} ), report.end());

        for (auto it : nextRep) {
            it.first->report(it.second);
        }

    }

    int Ai_Deep::revolve(Robot_Scout * mobile, int ret) {
        int top_cor_s, left_cor_s, bottom_cor_s, right_cor_s;
        mobile->determineCorers(top_cor_s, left_cor_s, bottom_cor_s, right_cor_s, mobile->getMaxRadius());
        //std::cout << "REVOLVING\n" << top_cor_s << " " << left_cor_s << " " << bottom_cor_s << " "  << right_cor_s << std::endl;
        auto * comm = dynamic_cast<Robot_Commander *>(mobile->getOwner());
        if(comm->manMod()->unknownSquare(top_cor_s, left_cor_s, bottom_cor_s, right_cor_s)) {
            comm->manMod()->addStep(mobile, mobile->getPosition(), (mobile->getDirection() + 1) % 4, envir->getTime()+1, 2);
            comm->manMod()->addStep(mobile, mobile->getPosition(), (mobile->getDirection() + 2) % 4, envir->getTime()+2, 2);
            comm->manMod()->addStep(mobile, mobile->getPosition(), (mobile->getDirection() + 3) % 4, envir->getTime()+3, 2);
            comm->manMod()->addStep(mobile, mobile->getPosition(), mobile->getDirection(), envir->getTime()+4, ret);

            return 1;
        } else {
            makeReport(mobile, ret);
            return 0;
        }
    }

    bool Ai_Deep::isOpened(coordinates pos) const {
        return !(ai_dict.find(pos) == ai_dict.end());
    }

    void Ai_Deep::makeReport(Robot_Scout *who, int type) {
        report.emplace_back(who, type);
    }

    void Ai_Deep::reported(std::deque<std::pair<Robot_Scout *, int>>::iterator delit) {
        (*delit).second = -1;
    }

    int Ai_Deep::pairRes(Robot_Commander * comm) {
        unsigned int ri = comm->ri();

        int top_cor_m, left_cor_m, bottom_cor_m, right_cor_m;
        comm->determineCorers(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m, comm->manMod()->getRadius());

        if(allOpened(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m)) {
            return 1;
        } else {
            auto grey = findGrey(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m);

            std::vector<std::vector<int>> leeTab = initLee(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m, comm);

            leeComp(leeTab, left_cor_m, bottom_cor_m, comm->getPair()->getPosition());


            std::sort(grey.begin(), grey.end(), [&](coordinates const & a, coordinates const &b) { return leeTab[a.y- bottom_cor_m][a.x - left_cor_m] < leeTab[b.y - bottom_cor_m][b.x - left_cor_m]; });

            std::cout << "BLOCKED_POINTS:" << std::endl;
            for (auto itBl : busyPoints) {
                std::cout << itBl.x << ";" << itBl.y << std::endl;
            }

            for (auto it : grey) {
                if (md->onRoute(it))
                    continue;
                //std::cout << "GREY" << std::endl;
                //std::cout << it.x << "," << it.y << " = " << leeTab[it.y - bottom_cor_m][it.x - left_cor_m] <<  std::endl;
                std::vector<coordinates> route;
                if (leeTab[it.y - bottom_cor_m][it.x - left_cor_m] > 0) {
                    makeRoute(leeTab, route, left_cor_m, bottom_cor_m, it);
                    for (auto coord = route.rbegin(); coord != route.rend(); ++coord) {
                        //std::cout << coord->x << ";" << coord->y << std::endl;

                        if (*coord == route[0])
                            md->routePoint(comm->getPair(), *coord, 5, envir->getTime());
                        else
                            md->routePoint(comm->getPair(), *coord, 2, envir->getTime());

                    }

                    break;
                }
            }

            return 0;
        }

    }

    int Ai_Deep::backToChief(Robot_Commander * comm) {
        int top_cor_m, left_cor_m, bottom_cor_m, right_cor_m;
        comm->determineCorers(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m, comm->manMod()->getRadius());

        coordinates target;
        if (comm->getDirection() == 0) {
            target = {comm->getX(), comm->getY()-1};
        } else if (comm->getDirection() == 1) {
            target = {comm->getX()+1, comm->getY()};
        } else if (comm->getDirection() == 2) {
            target = {comm->getX(), comm->getY()+1};
        } else if (comm->getDirection() == 3) {
            target = {comm->getX()-1, comm->getY()};
        }
        else
            throw std::invalid_argument("unknown direction : 2");

        std::vector<std::vector<int>> leeTab = initLee(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m, comm, &target);
        leeComp(leeTab, left_cor_m, bottom_cor_m, comm->getPair()->getPosition());

        std::cout << "BACK_HOME" << std::endl;

        std::vector<coordinates> route;
        makeRoute(leeTab, route, left_cor_m, bottom_cor_m, target);

        if (route.size() == 0)
            return 1;

        for (auto coord = route.rbegin(); coord != route.rend(); ++coord) {
            if (*coord == route[0])
                md->routePoint(comm->getPair(), *coord, 7, envir->getTime());
            else
                md->routePoint(comm->getPair(), *coord, 0, envir->getTime());
        }

        return 0;

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
            else {
                throw std::invalid_argument("Invalid LEE table");
            }

            route.push_back({curX, curY});
            ceil--;
        }
    }

    bool Ai_Deep::allOpened(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor) {
        //std::cout << top_cor << " " << left_cor << " " << bottom_cor << " "<< right_cor << std::endl;
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

    std::vector<coordinates> Ai_Deep::findAllGrey() {
        std::vector<coordinates> grey;

        for (auto pnt : ai_dict) {
            if(!pnt.second.topBoundaty) {
                if (ai_dict.find({static_cast<unsigned int>(pnt.first.x), static_cast<unsigned int>(pnt.first.y+1)}) == ai_dict.end()) {
                    grey.push_back(pnt.first);
                    continue;
                }
            }

            if(pnt.first.x > 0) {
                if (ai_dict.find({static_cast<unsigned int>(pnt.first.x-1), static_cast<unsigned int>(pnt.first.y)}) == ai_dict.end()) {
                    grey.push_back(pnt.first);
                    continue;
                }
            }

            if(pnt.first.y > 0) {
                if (ai_dict.find({static_cast<unsigned int>(pnt.first.x), static_cast<unsigned int>(pnt.first.y-1)}) == ai_dict.end()) {
                    grey.push_back(pnt.first);
                    continue;
                }
            }

            if(!pnt.second.rightBoundary) {
                if (ai_dict.find({static_cast<unsigned int>(pnt.first.x+1), static_cast<unsigned int>(pnt.first.y)}) == ai_dict.end()) {
                    grey.push_back(pnt.first);
                    continue;
                }
            }
        }

        return grey;
    }

    std::vector<coordinates> Ai_Deep::findWhite(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor) {
        std::vector<coordinates> white;

        for (unsigned int h = bottom_cor; h <= top_cor; ++h) {
            for (unsigned int w = left_cor; w <= right_cor; ++w) {
                coordinates coord = {w, h};
                auto p_val = ai_dict.find(coord);

                if (p_val == ai_dict.end())
                    white.push_back({w, h});

            }
        }

        return white;
    }

    std::vector<coordinates> Ai_Deep::findGreyRI(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor, int rad) {
        int radius = rad - 1;

        unsigned int big_top = top_cor + radius;
        unsigned int big_left;
        unsigned int big_bottom;
        unsigned int big_right = right_cor + radius;

        if (big_top >= envir->getHeight())
            big_top = envir->getHeight() - 1;

        if (big_right >= envir->getWidth())
            big_right = envir->getWidth() - 1;

        if (radius > left_cor)
            big_left = 0;
        else
            big_left = left_cor - radius;

        if (radius > bottom_cor)
            big_bottom = 0;
        else
            big_bottom = bottom_cor - radius;

        std::cout << big_top << " " << big_left << " " << big_bottom << " " << big_right << std::endl;

        std::vector<coordinates> ri_grey;
        std::vector<coordinates> big = findGrey(big_top, big_left, big_bottom, big_right);
        std::vector<coordinates> internal = findGrey(top_cor, left_cor, bottom_cor, right_cor);

        std::sort(big.begin(), big.end());
        std::sort(internal.begin(), internal.end());

        //std::set_difference(
        //        big.begin(), big.end(),
        //        internal.begin(), internal.end(),
        //        std::back_inserter(ri_grey)
        //        );

        for (auto it = big.begin(); it != big.end(); it++) {
            if (std::find(internal.begin(), internal.end(), *it) == internal.end()) {
                ri_grey.push_back((*it));
            }
        }

        std::cout << "-----------\nBIG\n--------------" << std::endl;
        for (auto it : big) {
            std::cout << it.x + left_cor << "," << it.y + bottom_cor << std::endl;
        }
        std::cout << "-----------\nEND\n--------------" << std::endl << std::endl;

        std::cout << "-----------\nINTERNAL\n--------------" << std::endl;
        for (auto it : internal) {
            std::cout << it.x + left_cor << "," << it.y + bottom_cor << std::endl;
        }
        std::cout << "-----------\nEND\n--------------" << std::endl << std::endl;

        return ri_grey;

    }

    std::vector<coordinates> Ai_Deep::findWhiteRI(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor, int radius) {
        unsigned int big_top = top_cor + radius;
        unsigned int big_left;
        unsigned int big_bottom;
        unsigned int big_right = right_cor + radius;

        if (big_top >= envir->getHeight())
            big_top = envir->getHeight() - 1;

        if (big_right >= envir->getWidth())
            big_right = envir->getWidth() - 1;

        if (radius > left_cor)
            big_left = 0;
        else
            big_left = left_cor - radius;

        if (radius > bottom_cor)
            big_bottom = 0;
        else
            big_bottom = bottom_cor - radius;

        std::vector<coordinates> ri_white;
        std::vector<coordinates> big = findWhite(big_top, big_left, big_bottom, big_right);
        std::vector<coordinates> internal = findWhite(top_cor, left_cor, bottom_cor, right_cor);

        std::sort(big.begin(), big.end());
        std::sort(internal.begin(), internal.end());

        //std::set_difference(
        //        big.begin(), big.end(),
        //        internal.begin(), internal.end(),
        //        std::back_inserter(ri_grey)
        //        );

        for (auto it = big.begin(); it != big.end(); it++) {
            if (std::find(internal.begin(), internal.end(), *it) == internal.end()) {
                ri_white.push_back((*it));
            }
        }

        return ri_white;
    }

    int Ai_Deep::riRes(robo::Robot_Commander * comm) {
        auto * subd = comm->getPair();

        int top_cor_m, left_cor_m, bottom_cor_m, right_cor_m;
        comm->determineCorers(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m, comm->manMod()->getRadius());
        //std::cout << top_cor_m << " " << left_cor_m << " " << bottom_cor_m << " " << right_cor_m << " " << static_cast<int>(subd->getMaxRadius()) << std::endl;

        /*auto grey = findGreyRI(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m, subd->getMaxRadius());
        std::cout << "RI_GREY_PRINT" << (*ai_dict.find({0, 53})).second.iam << std::endl;
        for (coordinates coord : grey) {
            std::cout << coord.x << ";" << coord.y << " ";
        }
        std::cout << std::endl;*/

        auto white = findWhiteRI(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m, subd->getMaxRadius());
        //std::cout << "\n#######RI_WHITE_PRINT" << std::endl;
        //for (coordinates coord : white) {
        //    std::cout << coord.x << ";" << coord.y << " ";
        //}
        //std::cout << std::endl;

        std::vector<std::vector<int>> leeTab = initLee(top_cor_m, left_cor_m, bottom_cor_m, right_cor_m, comm);
        leeComp(leeTab, left_cor_m, bottom_cor_m, subd->getPosition());

        std::vector<coordinates> route;
        int minway = -1;
        coordinates nearest;
        for (auto it : white) {
            auto mys = maySee(it, subd->getMaxRadius());
            for (auto my : mys) {
                if (my.y - bottom_cor_m < leeTab.size() && my.x - left_cor_m < leeTab[my.y - bottom_cor_m].size() && leeTab[my.y - bottom_cor_m][my.x - left_cor_m] > 0) {
                    if (minway < 0 || minway > leeTab[my.y - bottom_cor_m][my.x - left_cor_m]) {
                        minway = leeTab[my.y - bottom_cor_m][my.x - left_cor_m];
                        nearest = my;
                    }
                }
            }
        }

        if (minway < 0)
            return 1;

        //std::cout << " TO ::: " << nearest.x << ";" << nearest.y << " ";
        makeRoute(leeTab, route, left_cor_m, bottom_cor_m, {nearest.x, nearest.y});
        //std::cout << "RTTT" << std::endl;
        //for (auto coord = route.rbegin(); coord != route.rend(); ++coord) {
        //    std::cout << coord->x << ";" << coord->y << std::endl;
        //}
        for (auto coord = route.rbegin(); coord != route.rend(); ++coord) {
            if (*coord == route[0]) {
                md->routePoint(comm->getPair(), *coord, 10, envir->getTime());
            }
            else
                md->routePoint(comm->getPair(), *coord, 2, envir->getTime());
        }

        return 0;
    }

    std::vector<coordinates> Ai_Deep::maySee(coordinates obj, int radius) {
        std::vector<coordinates> ret;
        int y = static_cast<int>(obj.y);
        int x = static_cast<int>(obj.x);
        //std::cout << "CALCULATING " << x << ";" << y << std::endl;
        for (int h = y - radius; h <= y + radius; ++h) {
            for (int w = x - radius; w <= x + radius; ++w) {
                if (x != w || y != h) {
                    if (h >= 0 && w >= 0) {
                        if (md->onRoute({static_cast<unsigned int>(w), static_cast<unsigned int>(h)})) {
                            continue;
                        }
                        ret.push_back({static_cast<unsigned int>(w), static_cast<unsigned int>(h)});
                    }
                    //std::cout << " {" << w << ";" << h << "}";
                }
            }
        }
        //std::cout << std::endl;

        return ret;
    }

    std::vector<std::vector<int>> Ai_Deep::initLee(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor, const Robot_Commander * commander, const coordinates * target) {
        std::vector<int> row (right_cor - left_cor + 1);
        std::vector<std::vector<int>> leeTab (top_cor-bottom_cor+1);

        for (unsigned int h = bottom_cor; h <= top_cor; ++h) {
            leeTab[h-bottom_cor] = row;
            for (unsigned int w = left_cor; w <= right_cor; ++w) {
                coordinates coord = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                if(coord == commander->getPosition()) {
                    leeTab[h-bottom_cor][w-left_cor] = -4;
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

                coordinates cur = {w, h};
                if (checkBlocked({w, h}) && commander->getPosition() != cur) {
                    if (target == nullptr)
                        leeTab[h-bottom_cor][w-left_cor] = -2;
                    else if (*target != cur)
                        leeTab[h-bottom_cor][w-left_cor] = -2;
                }
            }
        }

        /*for (auto & ly : leeTab) {
            for(int & lx : ly) {
                if (lx >= 0)
                    std::cout << " ";
                if (lx < 10)
                    std::cout << " ";
                std::cout << lx << " ";
            }
            std::cout << std::endl;
        }*/

        return leeTab;
    }

    void Ai_Deep::leeComp(std::vector<std::vector<int>> & leeTable, unsigned int startX, unsigned int startY, coordinates start) {
        leeTable[start.y - startY][start.x - startX] = 0;

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

        /*for (auto & ly : leeTable) {
            for(int & lx : ly) {
                if (lx >= 0)
                    std::cout << " ";
                if (lx < 10)
                    std::cout << " ";
                std::cout << lx << " ";
            }
            std::cout << std::endl;
        }*/
    }

    void Ai_Deep::trainNext(Robot_Commander * comm) {
        auto grey = findAllGrey();

        unsigned int maxX = openedRightBoundary();;
        unsigned int maxY = openedTopBoundary();;

        for (auto g : grey) {
            if (g.x > maxX)
                maxX = g.x;
            if (g.y > maxY)
                maxY = g.y;
        }

        std::vector<std::vector<int>> leeTab = initLee(maxY, 0, 0, maxX, comm);
        leeComp(leeTab, 0, 0, comm->getPosition());

        std::sort(grey.begin(), grey.end(), [&](coordinates const & a, coordinates const &b) { return leeTab[a.y][a.x] < leeTab[b.y][b.x]; });

        //std::cout << "BA" << std::endl;
        //for (auto ca : busyArea) {
        //    std::cout << ca[0] << " * " << ca[1] << " * " << ca[2] << " * " << ca[3] << std::endl;
        //}

        if (grey.empty())
            setEnd();

        auto checkLee = leeAv();
        bool ava = false;
        bool deadend = true;

        for (auto g : grey) {
            //std::cout << "G " << g.x << ";" << g.y << std::endl;

            if (checkLee[g.y][g.x] > 0) {
                ava = true;
                std::vector<coordinates> route;


                coordinates last;
                if (leeTab[g.y][g.x] > 0) {
                    deadend = false;
                    if (!checkInAreas(g)) {
                        deleteBlockedPoint(comm->getPosition());
                        if (comm->getPair() != nullptr)
                            deleteBlockedPoint(comm->getPair()->getPosition());

                        unsigned int pairRad;
                        int top_cor_ri, left_cor_ri, bottom_cor_ri, right_cor_ri;
                        // in g.x, g.y
                        if (comm->getPair() != nullptr)
                            pairRad = dynamic_cast<Robot_Scout *>(comm->getPair())->getMaxRadius();
                        else
                            pairRad = comm->getMaxRadius();

                        Observation_Center::determineCorers(top_cor_ri, left_cor_ri, bottom_cor_ri, right_cor_ri,
                                                            comm->manMod()->getRadius() +
                                                            pairRad, g);

                        addArea(top_cor_ri, left_cor_ri, bottom_cor_ri, right_cor_ri);

                        makeRoute(leeTab, route, 0, 0, {g.x, g.y});
                        for (auto coord = route.rbegin(); coord != route.rend(); ++coord) {
                            std::cout << coord->x << ";" << coord->y << std::endl;
                            unsigned int atime;

                            if (*coord != *route.begin() || comm->getPair() != nullptr)
                                atime = md->routePoint(comm, *coord, 2, envir->getTime());
                            else
                                atime = md->routePoint(comm, *coord, 3, envir->getTime());

                            if (comm->getPair() != nullptr) {
                                if (coord == route.rbegin()) {
                                    //std::cout << "WAY " << comm->getX() << ";" << comm->getY() << " <- "
                                    //          << comm->getPair()->getX() << ";" << comm->getPair()->getY() << std::endl;
                                    md->routePoint(dynamic_cast<Robot_Scout *>(comm->getPair()), comm->getPosition(), 2,
                                                   atime + 1);
                                } else if (*coord != *route.begin()) {
                                    md->routePoint(dynamic_cast<Robot_Scout *>(comm->getPair()), last, 2, envir->getTime());
                                } else {
                                    md->routePoint(dynamic_cast<Robot_Scout *>(comm->getPair()), last, 3, envir->getTime());
                                }

                                last = *coord;
                            }
                        }

                        return;
                    }
                }
            }
        }

        if (deadend && comm->getPair() != nullptr) {
            coordinates sub = comm->getPair()->getPosition();

            std::cout << "DEADEND " << sub.x << ";" << sub.y << std::endl;
            coordinates tar[] = {{sub.x, sub.y+1}, {sub.x-1, sub.y}, {sub.x, sub.y-1}, {sub.x+1, sub.y}};
            auto surrPoint = ai_dict.begin();

            for (int i = 0; i < 4; ++i) {
                if (i == 1 && sub.x == 0)
                    continue;
                if (i == 2 && sub.y == 0)
                    continue;

                surrPoint = ai_dict.find(tar[i]);
                if (surrPoint != ai_dict.end() && comm->getPosition() != tar[i]) {
                    if ((surrPoint->second.iam == nullptr ||
                         !strcmp(typeid(*surrPoint->second.iam).name(), "N4robo14Interest_PointE")) &&
                        !checkBlocked(tar[i]) && !checkInAreas(tar[i])) {
                        if (!md->onRoute(tar[i])) {
                            deleteBlockedPoint(comm->getPosition());
                            addBlockedPoint(tar[i]);
                            md->routePoint(dynamic_cast<Robot_Scout *>(comm->getPair()), tar[i], 0, envir->getTime()+1);
                            md->routePoint(comm, sub, 11, envir->getTime()+2);
                            if (!ava) setEnd();
                            return;
                        }

                    }
                }
            }

        }

        md->addStep({comm, comm->getPosition(), comm->getDirection(), envir->getTime()+1, 11});

        if (!ava) setEnd();

    }

    unsigned int Ai_Deep::openedRightBoundary() const {
        for (auto a = ai_dict.rbegin(); a != ai_dict.rend(); ++a)
            if (a->second.rightBoundary)
                return a->first.x;
        return 0;
    }

    unsigned int Ai_Deep::openedTopBoundary() const {
        for (auto a : ai_dict)
            if (a.second.topBoundaty)
                return a.first.y;

        return 0;
    }

    std::dmultiset<std::array<unsigned int, 4>>::iterator Ai_Deep::checkArea(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor) {
        //std::cout << "FINDDDDING " << top_cor << " " << left_cor << " " << bottom_cor << " " << right_cor << std::endl;
        auto req = std::array<unsigned int, 4>({top_cor, left_cor, bottom_cor, right_cor});
        return busyArea.find(req);
    }

    bool Ai_Deep::checkInAreas(coordinates pnt) {
        for (auto it : busyArea) {
            if (pnt.y >= it[2] && pnt.y <= it[0] && pnt.x >= it[1] && pnt.x <= it[3]) {
                //std::cout << it[0] << " * " << it[1] << " * " << it[2] << " * " << it[3] << std::endl;
                //std::cout << pnt.x << ";" << pnt.y <<std::endl;
                return true;
            }
        }

        return false;
    }

    bool Ai_Deep::addArea(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor) {
        auto req = std::array<unsigned int, 4>({top_cor, left_cor, bottom_cor, right_cor});
        busyArea.insert(req);
    }

    void Ai_Deep::deleteArea(unsigned int top_cor, unsigned int left_cor, unsigned int bottom_cor, unsigned int right_cor) {
        auto ca = checkArea(top_cor, left_cor, bottom_cor, right_cor);
        if (ca != busyArea.end())
            busyArea.erase(ca);
    }

    int Ai_Deep::addBlockedPoint(coordinates pos) {
        if (busyPoints.find(pos) != busyPoints.end())
            return 1;

        busyPoints.insert(pos); //due to i have made multiset

        return 0;
    }

    bool Ai_Deep::checkBlocked(coordinates pos) {
        return busyPoints.find(pos) != busyPoints.end();
    }

    void Ai_Deep::deleteBlockedPoint(coordinates pos) {
        auto delPos = busyPoints.find(pos);
        if(delPos != busyPoints.end()) {
            busyPoints.erase(delPos);
        }
    }

    std::vector<std::vector<int>> Ai_Deep::leeAv() {
        std::vector<int> row (envir->getWidth());
        std::vector<std::vector<int>> leeTab (envir->getHeight());

        for (unsigned int h = 0; h <= envir->getHeight()-1; ++h) {
            leeTab[h] = row;
            for (unsigned int w = 0; w <= envir->getWidth() - 1; ++w) {
                coordinates coord = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};

                auto p_val = ai_dict.find(coord);
                if (p_val == ai_dict.end()) {
                    leeTab[h][w] = -2;
                    continue;
                }

                if(p_val->second.iam == nullptr || !strcmp(typeid(*p_val->second.iam).name(), "N4robo14Interest_PointE")) {
                    leeTab[h][w] = -1;
                } else {
                    leeTab[h][w] = -2;
                }
            }
        }

        leeTab[0][0] = 0;
        int curD = 0;
        while (true) {
            bool changed = false;
            for (int i = 0; i < leeTab.size(); ++i) {
                for (int j = 0; j < leeTab[i].size(); ++j) {
                    if (leeTab[i][j] == curD) {
                        if (i != leeTab.size() - 1 && leeTab[i+1][j] == -1) {
                            leeTab[i + 1][j] = curD + 1;
                            changed = true;
                        }

                        if (j != 0 && leeTab[i][j-1] == -1) {
                            leeTab[i][j - 1] = curD + 1;
                            changed = true;
                        }

                        if (i != 0 && leeTab[i-1][j] == -1) {
                            leeTab[i - 1][j] = curD + 1;
                            changed = true;
                        }

                        if (j != leeTab[i].size()-1 && leeTab[i][j+1] == -1) {
                            leeTab[i][j + 1] = curD + 1;
                            changed = true;
                        }
                    }

                }
            }
            if(!changed)
                break;
            curD++;
        }

        /*for (auto & ly : leeTab) {
            for(int & lx : ly) {
                if (lx >= 0)
                    std::cout << " ";
                if (lx < 10)
                    std::cout << " ";
                std::cout << lx << " ";
            }
            std::cout << std::endl;
        }*/

        return leeTab;
    }

}