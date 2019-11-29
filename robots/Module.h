#ifndef ROBOTSCREATE_MODULE_H
#define ROBOTSCREATE_MODULE_H

namespace robo {
    class Module {
    protected:
        Module() = delete;
        Module(int prior, bool act) : priority(prior), active(act) {}
        int priority;
        bool active;
    public:
        int getPriority();
        bool getActive();
        int setActive();

        Module * copy() const; // TODO for children? (ABS VIRTUAL)
    };
}

#endif //ROBOTSCREATE_MODULE_H
