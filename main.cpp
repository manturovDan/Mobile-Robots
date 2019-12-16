#include <iostream>

//#include "robots/robot.h"
#include "robots/interface.h"
#include "robots/Display.h"
#include "robots/Ai_Deep.h"

template <class T>
int inpNum(T &inp, bool unneg = false, const char *again = "Input error! Try again!") {
    bool more = false;
    while (1) {
        if (more)
            std::cout << again << std::endl;

        std::cin >> inp;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            more = 1;
            continue;
        }
        if(std::abs(inp) > 100000000 || (unneg && inp < 0))
            more = true;
        else
            return 0;
    }
}

int inpString(std::string &inp, const char *again, std::ostream &stream) {
    bool more = false;
    while (1) {
        if (more)
            std::cout << again << std::endl;

        std::cin >> inp;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            more = 1;
            continue;
        }

        return 0;
    }
}

int chooseAct() {
    int choise;
    while(1) {
        std::cout << "Choose the number\n\
    0. Exit\n\
    1. Generate environment\n\
    2. Load environment from xml\n\
    3. Create environment" << std::endl;

        inpNum(choise);
        if (choise >= 0 && choise <= 3)
            return choise;

        std::cout << "Incorrect value! Try again!\n" << std::endl;
    }
}

int launchFunc(int act, robo::Environment_describer * env) {
    if (act == 1) {
        return 0;
    } else if (act == 2) {
        interf::EnvXMLCreate("/home/danila/source/robots/storage/map6.xml", *env);
        auto itf = interf::InterfaceTools(env);
        auto ai = robo::Ai_Deep(env);
        robo::Managing::setAI(&ai);

        //itf.printEnv();
        itf.printEnv();
        //ai.print(std::cout);

        dispr::Display disp(env, & ai);
        disp.run();
        return 0;
    } else if (act == 3) {
        env->setHeight(15);
        env->setWidth(20);
        return 0;
    }
}

int main()
{
    robo::Environment_describer env;
    //robo::Map_Object *obs1 = env.setObject({10, 10, 1}, "Obstacle");

    //std::cout << "MOBILE ROBOTS ONE" << std::endl;
    std::cout << "\n __  __  ____  ____ _____ _      ______   _____   ____  ____   ____ _______ _____ \n"
                 "|  \\/  |/ __ \\|  _ \\_   _| |    |  ____| |  __ \\ / __ \\|  _ \\ / __ \\__   __/ ____|\n"
                 "| \\  / | |  | | |_) || | | |    | |__    | |__) | |  | | |_) | |  | | | | | (___  \n"
                 "| |\\/| | |  | |  _ < | | | |    |  __|   |  _  /| |  | |  _ <| |  | | | |  \\___ \\ \n"
                 "| |  | | |__| | |_) || |_| |____| |____  | | \\ \\| |__| | |_) | |__| | | |  ____) |\n"
                 "|_|  |_|\\____/|____/_____|______|______| |_|  \\_\\\\____/|____/ \\____/  |_| |_____/ \n\n" << std::endl;

    int choise;
    while (1) {
        choise = chooseAct();
        if (!choise)
            return 0;
        launchFunc(choise, &env);
    }
}