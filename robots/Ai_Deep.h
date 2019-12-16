#ifndef ROBOTSCREATE_AI_DEEP_H
#define ROBOTSCREATE_AI_DEEP_H

#include <map>
#include <set>
#include <array>
#include <deque>

#include "../multiset/multiset.h"

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
    private:
        std::map<coordinates, map_point> ai_dict;
        std::multimap<unsigned int, Map_Object *> commanders;
        std::multimap<unsigned int, Map_Object *> scouts;
        std::deque<std::pair<Robot_Scout *, int>> report;
        Moving_Describer * md;
        Environment_describer * envir;
        std::set<std::array<unsigned int, 4>> busyArea;
        std::set<coordinates> busyPoints;
        bool theEnd = false;
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
        bool isOpened(coordinates) const;
        Moving_Describer * getMd() { return md; }
        std::multimap<coordinates, map_point>::const_iterator begin() { return ai_dict.begin(); }
        std::multimap<coordinates, map_point>::const_iterator end() { return ai_dict.end(); }
        int startCommander();
        void nextComp();
        void makeReport(Robot_Scout *, int);
        void reported(std::deque<std::pair<Robot_Scout *, int>>::iterator);
        ///returns 1 if all points are opened 0 - else
        int pairRes(Robot_Commander *);
        int riRes(Robot_Commander *);
        std::vector<coordinates> maySee(coordinates, int);
        int backToChief(Robot_Commander *);
        int revolve(Robot_Scout *, int);
        bool allOpened(unsigned int, unsigned int, unsigned int, unsigned int);
        std::vector<coordinates> findGrey(unsigned int, unsigned int, unsigned int, unsigned int);
        std::vector<coordinates> findAllGrey();
        std::vector<coordinates> findWhite(unsigned int, unsigned int, unsigned int, unsigned int);
        std::vector<coordinates> findGreyRI(unsigned int, unsigned int, unsigned int, unsigned int, int);
        std::vector<coordinates> findWhiteRI(unsigned int, unsigned int, unsigned int, unsigned int, int);
        /// return matrix with 0 - free for moving, 1 - unreachable
        std::vector<std::vector<int>> initLee(unsigned int, unsigned int, unsigned int, unsigned int, const Robot_Commander *, const coordinates * target = nullptr);
        void leeComp(std::vector<std::vector<int>> &, unsigned int, unsigned int, coordinates);
        std::vector<std::vector<int>> leeAv();
        void makeRoute(std::vector<std::vector<int>> &, std::vector<coordinates> &, unsigned int, unsigned int, coordinates);
        void trainNext(Robot_Commander *);
        unsigned int openedRightBoundary() const;
        unsigned int openedTopBoundary() const;
        bool getEnd() const { return theEnd; }
        void setEnd() { theEnd = true; }
        /// returns 1 if area is busy, else 0
        std::set<std::array<unsigned int, 4>>::iterator checkArea (unsigned int, unsigned int, unsigned int, unsigned int) const;
        /// return 1 if point is busy, else 0
        bool checkInAreas(coordinates) const;
        ///true if successfully
        bool addArea(unsigned int, unsigned int, unsigned int, unsigned int);
        void deleteArea(unsigned int, unsigned int, unsigned int, unsigned int);
        int addBlockedPoint(coordinates);
        void deleteBlockedPoint(coordinates);
        bool checkBlocked(coordinates);
    };
}


#endif //ROBOTSCREATE_AI_DEEP_H
