#ifndef ROBOTSCREATE_DISPLAY_H
#define ROBOTSCREATE_DISPLAY_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

#include "Environment_describer.h"
#include "Ai_Deep.h"

namespace dispr {
    class Display {
    private:
        robo::Environment_describer * env;
        robo::Ai_Deep * ai;
        std::mutex sw;
        bool is_comp;
        std::ostream & os;
        std::istream & is;
        std::mutex m;
    public:
        Display() = delete;
        Display(robo::Environment_describer *, robo::Ai_Deep *, std::ostream & ostr = std::cout, std::istream & istr = std::cin);
        void show();
        void run();
        void justTimer();

        void computing();
        void draw();
    };
}

#endif //ROBOTSCREATE_DISPLAY_H
