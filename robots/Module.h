#ifndef ROBOTSCREATE_MODULE_H
#define ROBOTSCREATE_MODULE_H

#include <iostream>

namespace robo {
    class Module {
    protected:
        Module() = delete;
        Module(int prior, bool act) : priority(prior), active(act) {}
        int priority;
        bool active;
    public:
        int getPriority();
        bool getActive() { return active; }
        int setActive();

        virtual std::string whoami() = 0;
        virtual Module * copy() = 0;
    };
}

#endif //ROBOTSCREATE_MODULE_H
