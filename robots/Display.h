#ifndef ROBOTSCREATE_DISPLAY_H
#define ROBOTSCREATE_DISPLAY_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>

#include "Environment_describer.h"
#include "Ai_Deep.h"

namespace dispr {
    class Display {
    private:
        robo::Environment_describer * env;
        robo::Ai_Deep * ai;
        std::mutex sw;
        std::condition_variable time_upd;
    public:
        Display() = delete;
        Display(robo::Environment_describer *, robo::Ai_Deep *);
        void show();
        void run();
        void justTimer();
    };
}

#endif //ROBOTSCREATE_DISPLAY_H
