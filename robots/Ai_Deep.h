#ifndef ROBOTSCREATE_AI_DEEP_H
#define ROBOTSCREATE_AI_DEEP_H

#include <map>
#include <deque>
#include "robot.h"
#include "Managing.h"
#include "Moving_Describer.h"

namespace robo {
    struct map_point {
        Map_Object * iam;
        bool topBoundaty;
        bool rightBoundary;
    };

    class Robot_Commander;

    class Ai_Deep {
    public:
        Ai_Deep() = delete;
        explicit Ai_Deep(Environment_describer *);
        void add_point(Map_Object *);
        void print(std::ostream & stream = std::cout);
        void researchMap();
        void connectResult(const std::map<coordinates, Map_Object *> &);
        void print_d(int, int, std::ostream & stream = std::cout);
        void run();
        void testMove();
        void testNext();
        bool isOpened(coordinates);
        Moving_Describer * getMd() { return md; }
        std::multimap<coordinates, map_point>::const_iterator begin() { return ai_dict.begin(); }
        std::multimap<coordinates, map_point>::const_iterator end() { return ai_dict.end(); }
        int startCommander();
        void nextComp();
        void makeReport(Robot_Scout *, int);
        void reported(std::deque<std::pair<Robot_Scout *, int>>::iterator);
        void pairRes(Robot_Commander *);
        bool allOpened(unsigned int, unsigned int, unsigned int, unsigned int);
    private:
        std::map<coordinates, map_point> ai_dict;
        std::multimap<unsigned int, Map_Object *> commanders;
        std::multimap<unsigned int, Map_Object *> scouts;
        std::deque<std::pair<Robot_Scout *, int>> report;
        Moving_Describer * md;
        Environment_describer * envir;
    };
}


#endif //ROBOTSCREATE_AI_DEEP_H
