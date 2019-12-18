#include "Display.h"

namespace dispr {
    Display::Display(robo::Environment_describer * envir, robo::Ai_Deep *aip, std::ostream & ostr, std::istream & istr)
    : env(envir), ai(aip), os(ostr), is(istr), is_comp(false) { m.unlock(); }

    void Display::computing() {
        ai->run();
        using namespace std::chrono_literals;
        os << "START" << std::endl;

        int i = 0;
        while (true) {
            if (closed)
                return;
            auto start = std::chrono::high_resolution_clock::now();
            std::this_thread::sleep_for(0.1s);
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

        os << "THE END!\nPress any key to exit" << std::endl;

        is.ignore();
        is.get();
        closed = true;
    }

    void Display::draw() {
        std::vector<std::vector<std::pair<sf::Sprite, int>>> viz; /// sprite and direction for mobile robots
        std::set<std::pair<unsigned int, unsigned int>> mobile;

        viz.resize(env->getHeight());
        for (auto & i : viz) {
            i.resize(env->getWidth());
        }

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


        while (window.isOpen()) {
            if (closed) {
                viz.clear();
                mobile.clear();
                window.clear();
                window.close();
                exit(0);
            }

            if (!is_comp)
                continue;


            if (m.try_lock()) {
                mobile.clear();

                for (unsigned int i = 0; i < env->getHeight(); ++i) {
                    for (unsigned int j = 0; j < env->getWidth(); ++j) {
                        viz[i][j] = std::pair<sf::Sprite, int> (landNoS, 0);
                    }
                }

                for(robo::Env_Consistent_Iter it = env->begin(); it != env->end(); ++it) {
                    float x = (*it)->getX();
                    float y = (*it)->getY();

                    if(!strcmp(typeid(**it).name(), "N4robo8ObstacleE")) {
                        viz[y][x] = std::pair<sf::Sprite, int> (obsNoS, 0);
                    }
                    else if(!strcmp(typeid(**it).name(), "N4robo14Interest_PointE")) {
                        viz[y][x] = std::pair<sf::Sprite, int> (intNoS, 0);
                    }
                    else if(!strcmp(typeid(**it).name(), "N4robo14Command_CenterE")) {
                        viz[y][x] = std::pair<sf::Sprite, int> (comcS, 0);
                    }
                    else if(!strcmp(typeid(**it).name(), "N4robo18Observation_CenterE")) {
                        viz[y][x] = std::pair<sf::Sprite, int> (obsS, 0);
                    }

                }

                for(const auto & it : *ai) {
                    if (it.second.iam == nullptr) {
                        viz[it.first.y][it.first.x] = std::pair<sf::Sprite, int> (lanOS, 0);
                    } else {
                        if(!strcmp(typeid(*it.second.iam).name(), "N4robo14Interest_PointE")) {
                            viz[it.first.y][it.first.x] = std::pair<sf::Sprite, int> (intOS, 0);
                        }
                        if(!strcmp(typeid(*it.second.iam).name(), "N4robo8ObstacleE")) {
                            viz[it.first.y][it.first.x] = std::pair<sf::Sprite, int> (obsOS, 0);
                        }
                    }
                }

                for(robo::Env_Consistent_Iter it = env->begin(); it != env->end(); ++it) {
                    float x = (*it)->getX();
                    float y = (*it)->getY();

                    if (!strcmp(typeid(**it).name(), "N4robo15Robot_CommanderE")) {
                        auto *curCom = dynamic_cast<robo::Robot_Commander *>(*it);
                        if (!curCom->getBlocked()) {
                            viz[y][x] = std::pair<sf::Sprite, int>(commanderS, curCom->getDirection());
                            mobile.emplace(y, x);
                        }

                    } else if (!strcmp(typeid(**it).name(), "N4robo11Robot_ScoutE")) {
                        auto *curSc = dynamic_cast<robo::Robot_Scout *>(*it);
                        if (!curSc->getBlocked()) {
                            viz[y][x] = std::pair<sf::Sprite, int>(scoutS, curSc->getDirection());
                            mobile.emplace(y, x);
                        }
                    }
                }

                m.unlock();
            }

            view.zoom(1.f + zoom);
            if (zoom != 0.f) {
                zoom = 0.f;
            }
            window.setView(view);
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    std::cout << "CLOSING" << std::endl;
                    closed = true;
                    viz.clear();
                    mobile.clear();
                    window.clear();
                    window.close();
                    exit(0);
                }
            }

            view.setCenter(static_cast<float >(winWidth)/2 + right, static_cast<float>(winHeight)/2 - up);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
                zoom += 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
                zoom -= 0.1f;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                up += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                up -= 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                right += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                right -= 10;
            }

            window.clear(sf::Color::White);

            for (unsigned int i = 0; i < env->getHeight(); ++i) {
                for (unsigned int j = 0; j < env->getWidth(); ++j) {
                    if (mobile.find(std::pair<unsigned int, unsigned int>(i, j)) == mobile.end()) {
                        viz[i][j].first.setPosition(static_cast<float>(j) * rectSize,
                                                    winHeight - rectSize - static_cast<float>(i) * rectSize);
                    }
                    else {
                        viz[i][j].first.setPosition(static_cast<float>(j)*rectSize + rectSize / 2, winHeight - rectSize - static_cast<float>(i)*rectSize + rectSize / 2);
                        viz[i][j].first.setOrigin({8, 8});

                        if (viz[i][j].second == 0) {
                            viz[i][j].first.setRotation(0);
                        }
                        if (viz[i][j].second== 1) {
                            viz[i][j].first.setRotation(-90.f);
                        }
                        if (viz[i][j].second == 2) {
                            viz[i][j].first.setRotation(-180.f);
                        }
                        if (viz[i][j].second == 3) {
                            viz[i][j].first.setRotation(90.f);
                        }
                    }

                    window.draw(viz[i][j].first);
                }
            }


            window.display();

        }
    }

    void Display::run() {
        std::thread trComp = std::thread(&Display::computing, this);
        std::thread trDraw = std::thread(&Display::draw, this);

        trComp.join();
        trDraw.join();
    }
}