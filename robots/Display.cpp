#include "Display.h"

namespace dispr {
    Display::Display(robo::Environment_describer * envir, robo::Ai_Deep *aip, std::ostream & ostr, std::istream & istr)
    : env(envir), ai(aip), os(ostr), is(istr), is_comp(false) { m.unlock(); }

    void Display::show() {
        const int winWidth = 700;
        const int winHeight = 700;
        const int rectSize = 16;

        float up = 0;
        float right = 0;

        sf::RenderWindow window (sf::VideoMode(winWidth, winHeight), "Mobile Robots");
        sf::View view;

        view.setSize(sf::Vector2f(winWidth, winHeight));
        view.setCenter(static_cast<float >(winWidth)/2, static_cast<float>(winHeight)/2);

        window.setFramerateLimit(32);

        float zoom = 0.f;

        unsigned int realTime = 0;


        sf::Texture landNoT;
        landNoT.loadFromFile("../static/land_no.jpg");
        sf::Sprite landNoS(landNoT);

        sf::Texture obsNoT;
        obsNoT.loadFromFile("../static/obs_no.jpg");
        sf::Sprite obsNoS(obsNoT);

        sf::Texture intNoT;
        intNoT.loadFromFile("../static/int_no.jpg");
        sf::Sprite intNoS(intNoT);

        sf::Texture comcT;
        comcT.loadFromFile("../static/com_cen.jpg");
        sf::Sprite comcS(comcT);

        sf::Texture obsT;
        obsT.loadFromFile("../static/observ.jpg");
        sf::Sprite obsS(obsT);

        sf::Texture lanOT;
        lanOT.loadFromFile("../static/land_o.jpg");
        sf::Sprite lanOS(lanOT);

        sf::Texture intOT;
        intOT.loadFromFile("../static/int_o.jpg");
        sf::Sprite intOS(intOT);

        sf::Texture obsOT;
        obsOT.loadFromFile("../static/obs_o.jpg");
        sf::Sprite obsOS(obsOT);

        sf::Texture commanderT;
        commanderT.loadFromFile("../static/commander.jpg");
        sf::Sprite commanderS(commanderT);

        sf::Texture scoutT;
        scoutT.loadFromFile("../static/scout.jpg");
        sf::Sprite scoutS(scoutT);

        while(window.isOpen()) {
            view.zoom(1.f + zoom);
            if (zoom != 0.f) {
                zoom = 0.f;
            }
            window.setView(view);
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            view.setCenter(static_cast<float >(winWidth)/2 + right, static_cast<float>(winHeight)/2 - up);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
                zoom += 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
                zoom -= 0.1f;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                //if (up < rectSize*env->getHeight() - winHeight)
                    up += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                //if (up > 0)
                    up -= 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                //if (right < rectSize*env->getWidth() - winWidth)
                    right += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                //if (right > 0)
                    right -= 10;
            }

            //std::cout << "PARAMS:" << zoom << " " << up << " " << right << std::endl;

            window.clear(sf::Color::White);

            for (unsigned int j = 0; j < env->getHeight(); ++j) {
                for (unsigned int i = 0; i < env->getWidth(); ++i) {
                    landNoS.setPosition(static_cast<float>(i)*rectSize, winHeight - rectSize -static_cast<float>(j)*rectSize);
                    window.draw(landNoS);
                }
            }

            for(robo::Env_Consistent_Iter it = env->begin(); it != env->end(); ++it) {
                float x = (*it)->getX();
                float y = (*it)->getY();

                if(!strcmp(typeid(**it).name(), "N4robo8ObstacleE")) {
                    obsNoS.setPosition(static_cast<float>(x)*rectSize, winHeight - rectSize -static_cast<float>(y)*rectSize);
                    window.draw(obsNoS);
                }
                if(!strcmp(typeid(**it).name(), "N4robo14Interest_PointE")) {
                    intNoS.setPosition(static_cast<float>(x)*rectSize, winHeight - rectSize -static_cast<float>(y)*rectSize);
                    window.draw(intNoS);
                }
                if(!strcmp(typeid(**it).name(), "N4robo14Command_CenterE")) {
                    comcS.setPosition(static_cast<float>(x)*rectSize, winHeight - rectSize -static_cast<float>(y)*rectSize);
                    window.draw(comcS);
                }
                if(!strcmp(typeid(**it).name(), "N4robo18Observation_CenterE")) {
                    obsS.setPosition(static_cast<float>(x)*rectSize, winHeight - rectSize -static_cast<float>(y)*rectSize);
                    window.draw(obsS);
                }

            }

            for(const auto & it : *ai) {
                if (it.second.iam == nullptr) {
                    lanOS.setPosition(static_cast<float>(it.first.x)*rectSize, winHeight - rectSize -static_cast<float>(it.first.y)*rectSize);
                    window.draw(lanOS);
                } else {
                    if(!strcmp(typeid(*it.second.iam).name(), "N4robo14Interest_PointE")) {
                        intOS.setPosition(static_cast<float>(it.first.x)*rectSize, winHeight - rectSize -static_cast<float>(it.first.y)*rectSize);
                        window.draw(intOS);
                    }
                    if(!strcmp(typeid(*it.second.iam).name(), "N4robo8ObstacleE")) {
                        obsOS.setPosition(static_cast<float>(it.first.x)*rectSize, winHeight - rectSize -static_cast<float>(it.first.y)*rectSize);
                        window.draw(obsOS);
                    }
                }
            }

            for(robo::Env_Consistent_Iter it = env->begin(); it != env->end(); ++it) {
                if(!strcmp(typeid(**it).name(), "N4robo15Robot_CommanderE")) {
                    auto * curCom = dynamic_cast<robo::Robot_Commander *>(*it);
                    if (!curCom->getBlocked()) {

                        commanderS.setPosition(static_cast<float>(curCom->getX())*rectSize + rectSize / 2, winHeight - rectSize - static_cast<float>(curCom->getY())*rectSize + rectSize / 2);
                        commanderS.setOrigin({8, 8});

                        if (curCom->getDirection() == 0) {
                            commanderS.setRotation(0);
                        }
                        if (curCom->getDirection() == 1) {
                            commanderS.setRotation(-90.f);
                        }
                        if (curCom->getDirection() == 2) {
                            commanderS.setRotation(-180.f);
                        }
                        if (curCom->getDirection() == 3) {
                            commanderS.setRotation(90.f);
                        }

                        window.draw(commanderS);
                    }

                }
                if(!strcmp(typeid(**it).name(), "N4robo11Robot_ScoutE")) {
                    auto * curSc = dynamic_cast<robo::Robot_Scout *>(*it);
                    if (!curSc->getBlocked()) {
                        scoutS.setPosition(static_cast<float>(curSc->getX())*rectSize + rectSize / 2, winHeight - rectSize - static_cast<float>(curSc->getY())*rectSize + rectSize / 2);
                        scoutS.setOrigin({8, 8});

                        if (curSc->getDirection() == 0) {
                            scoutS.setRotation(0);
                        }
                        if (curSc->getDirection() == 1) {
                            scoutS.setRotation(-90.f);
                        }
                        if (curSc->getDirection() == 2) {
                            scoutS.setRotation(-180.f);
                        }
                        if (curSc->getDirection() == 3) {
                            scoutS.setRotation(90.f);
                        }

                        window.draw(scoutS);
                    }

                }
            }

            unsigned int curTime = env->getTime();
            if(!is_comp) {
                //std::cout << "UPDDD" << std::endl;
                realTime = curTime;
                is_comp = true;
            }


            window.display();
        }
    }

    void Display::justTimer() {
        ai->run();

        using namespace std::chrono_literals;
        os << "Hello waiter\n" << std::flush;
        //ai->getMd()->printSteps();

        int i = 1;
        while(true) {
            if (is_comp) { // USE MUTEX
                auto start = std::chrono::high_resolution_clock::now();
                std::this_thread::sleep_for(0.01s); //TIME
                env->plusTime();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = end - start;
                //std::cout << "ROBOWORLD Time: " << env->getTime() << "; Waited " << elapsed.count() << " ms\n";
                if (ai->getEnd()) {
                    is_comp = false;
                    break;
                }
                ai->nextComp();
                if(ai->getMd()->makeSteps(env->getTime()))
                    ai->setEnd();
                is_comp = false;
                if (i++ == std::numeric_limits<unsigned int>::max() - 1)
                    break; // error
            }
        }
        os << "THE END DETECTION - Press any key to continue" << std::endl;
        is.ignore();
        is.get();

        os << "END THREADS" << std::endl;
    }

    void Display::computing() {
        ai->run();
        using namespace std::chrono_literals;
        os << "START" << std::endl;

        int i = 0;
        while (true) {
            auto start = std::chrono::high_resolution_clock::now();
            std::this_thread::sleep_for(0.01s);
            env->plusTime();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;

            if (ai->getEnd()) {
                break;
            }

            m.lock();
            ai->nextComp();
            if(ai->getMd()->makeSteps(env->getTime()))
                ai->setEnd();
            is_comp = true;
            if (i++ == std::numeric_limits<unsigned int>::max() - 1) {
                os << "Time limit was exceeded" << std::endl;
                break;
            }
            m.unlock();
        }
    }

    void Display::draw() {

    }

    void Display::run() {
        std::thread trDisp = std::thread(&Display::show, this);
        std::thread trInte = std::thread(&Display::justTimer, this);

        //std::thread trComp = std::thread(&Display::computing, this);
        //std::thread trDraw = std::thread(&Display::computing, this);

        trDisp.join();
        trInte.join();
    }
}