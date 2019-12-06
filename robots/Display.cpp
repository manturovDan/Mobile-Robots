#include "Display.h"

namespace dispr {
    Display::Display(robo::Environment_describer * envir) : env(envir) { }

    void Display::show() {
        std::unique_lock<std::mutex> lock(sw);

        sf::RenderWindow window (sf::VideoMode(700, 700), "Mobile Robots");

        window.setFramerateLimit(32);

        int k = 0;
        while(window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            sf::RectangleShape rectangle (sf::Vector2f(32, 32));

            sf::Texture landNoT;
            landNoT.loadFromFile("../static/land_no.jpg");
            sf::Sprite landNoS(landNoT);

            for (int j = 0; j < 50; ++j) {
                for (int i = 0; i < 50; ++i) {
                    rectangle.setFillColor(sf::Color::Blue);

                    rectangle.setPosition(i*32, j*32);
                    window.draw(rectangle);
                }
            }

            landNoS.setPosition(32+k*10, 32);
            window.draw(landNoS);

            //window.draw(TestCirc);
            window.display();
            k++;
            time_upd.wait(lock);
        }
    }

    void Display::justTimer() {
        using namespace std::chrono_literals;
        std::cout << "Hello waiter\n" << std::flush;
        int i = 1;
        while(true) {
            auto start = std::chrono::high_resolution_clock::now();
            std::this_thread::sleep_for(2s);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            std::cout << "Waited " << elapsed.count() << " ms\n";
            time_upd.notify_one();
            if (i++ == 1000)
                break;
        }
    }

    void Display::run() {
        std::thread trDisp = std::thread(&Display::show, this);
        std::thread trInte = std::thread(&Display::justTimer, this);
        trDisp.join();
        trInte.join();
    }
}