#ifndef ROBOTSCREATE_AI_DEEP_H
#define ROBOTSCREATE_AI_DEEP_H

#include <map>
#include "robot.h"
#include "Managing.h"

namespace robo {
    struct map_point {
        Map_Object * iam;
        bool isBoundary;
    };

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
        std::multimap<coordinates, map_point>::const_iterator begin() { return ai_dict.begin(); }
        std::multimap<coordinates, map_point>::const_iterator end() { return ai_dict.end(); }
    private:
        std::map<coordinates, map_point> ai_dict;
        std::multimap<unsigned int, Map_Object *> commanders;
        std::multimap<unsigned int, Map_Object *> scouts;
    };
}


#endif //ROBOTSCREATE_AI_DEEP_H
