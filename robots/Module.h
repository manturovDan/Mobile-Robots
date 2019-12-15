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
        int getPriority() const { return priority; }
        bool getActive() const { return active; }
        void activate() { active = true; }
        void deactivate() { active = false; }

        virtual std::string whoami() = 0;
        virtual Module * copy() = 0;
        virtual ~Module() = default;
    };
}

#endif //ROBOTSCREATE_MODULE_H
