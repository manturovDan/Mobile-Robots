#include "Display.h"

namespace dispr {
    Display::Display(robo::Environment_describer * envir) : env(envir) {
        sf::RenderWindow window(sf::VideoMode(700, 700), "Mobile Robots");

        sf::CircleShape TestCirc(350.f);
        TestCirc.setFillColor(sf::Color::Green);

        sf::RectangleShape rectangle (sf::Vector2f(32, 32));

        sf::Texture landNoT;
        landNoT.loadFromFile("../static/land_no.jpg");
        sf::Sprite landNoS(landNoT);

        window.setFramerateLimit(15);

        while(window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            for (int j = 0; j < 50; ++j) {
                for (int i = 0; i < 50; ++i) {
                    rectangle.setFillColor(sf::Color::Blue);

                    rectangle.setPosition(i*32, j*32);
                    window.draw(rectangle);
                }
            }

            landNoS.setPosition(32, 32);
            window.draw(landNoS);

            //window.draw(TestCirc);
            window.display();
        }
    }
}