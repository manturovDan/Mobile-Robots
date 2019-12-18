#include <iostream>

#include "robots/interface.h"
#include "robots/Display.h"
#include "robots/Ai_Deep.h"

template <class T>
int inpSmt(T &inp, const char *again = "Input error! Try again!") {
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

        else
            return 0;
    }
}

int chooseAct() {
    int choise;
    while(1) {
        std::cout << "Choose the number\n\
    0. Exit\n\
    1. Load environment from xml" << std::endl;

        inpSmt(choise);
        if (choise >= 0 && choise <= 1)
            return choise;

        std::cout << "Incorrect value! Try again!\n" << std::endl;
    }
}

int launchFunc(int act, robo::Environment_describer * env) {
    if (act == 1) {
        std::cout << "Input path to XML-file of map" << std::endl;
        std::string fileName;
        inpSmt(fileName);
        try {
            interf::EnvXMLCreate(fileName, *env);
            auto itf = interf::InterfaceTools(env);
            auto ai = robo::Ai_Deep(env);
            robo::Managing::setAI(&ai);

            dispr::Display disp(env, &ai);
            disp.run();
            return 0;
        }
        catch (std::exception &ex) {
            std::cerr << ex.what() << std::endl << "Try again!\n" << std::endl;
        }
    }

    return 1;
}

int main()
{
    robo::Environment_describer env;

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