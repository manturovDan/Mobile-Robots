#include "Observation_Center.h"
#include "Sensor.h"

namespace robo {
    Observation_Center::Observation_Center(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods,
                                           std::string & desc, coordinates pos) : Map_Object(pos), description(desc), cost(price), countPorts(ports), energyConsumption(consumption), appeared(true) {
        initModules(mods);
    }

    void Observation_Center::initModules(const std::vector<Module *> & modul) {
        if (countPorts < modul.size())
            throw std::invalid_argument("Robot has too many modules");

        for (auto itm : modul) {
            modules.push_back((*itm).copy());
        }
    }

    void Observation_Center::checkFree() {
        if (getCountModules() >= getCountPorts())
            throw std::invalid_argument("Count of modules exceeds count of ports");
    }

    std::string Observation_Center::whoami() {
        std::stringstream ss;
        ss << "Object : Observation_Center: {" << position.x << ", " << position.y << "}\nDesc: '" << description << "';\n"
                                           "Consumption: " << energyConsumption << ";\nCost: " << cost << ";\n"
                                           "PortsCount: " << countPorts << ";\nAppeared: " << appeared << std::endl;
        return ss.str();
    }

    int Observation_Center::look() {
        for (auto & module : modules) {
            if(!strcmp(typeid(*module).name(), "N4robo6SensorE") && module->getActive()) {
                auto * sens = static_cast<robo::Sensor *>(module);

                std::cout << "Active Senor rad = " << sens->getRadius() << " dir = " << sens->getDirection() << " angle = " << sens->getAngle() << std::endl;

                unsigned int real_dir = sens->getDirection(); //if will be direction of robot

                if (sens->getAngle() == 2) {
                    int left_cor = position.x - sens->getRadius();
                    if (left_cor < 0)
                        left_cor = 0;

                    int right_cor = position.x + sens->getRadius();
                    if (right_cor >= env->getWidth())
                        right_cor = env->getWidth() - 1;

                    int top_cor = position.y + sens->getRadius();
                    if (top_cor >= env->getHeight())
                        top_cor = env->getHeight() - 1;

                    int bottom_cor = position.y - sens->getRadius();
                    if (bottom_cor < 0)
                        bottom_cor = 0;

                    for (int h = top_cor; h >= bottom_cor; --h) {
                        for (int w = left_cor; w <= right_cor; ++w) {
                            if (getX() == w && getY() == h)
                                std::cout << " ########## ";
                            else
                                std::cout << " { " << w << ", " << h << " } ";
                        }
                        std::cout << std::endl;
                    }
                }
                else {
                    if (real_dir == 0) {
                        int left_cor = position.x - sens->getRadius();
                        if (left_cor < 0)
                            left_cor = 0;

                        int right_cor = position.x + sens->getRadius();
                        if (right_cor >= env->getWidth())
                            right_cor = env->getWidth() - 1;

                        int top_cor = position.y + sens->getRadius();
                        if (top_cor >= env->getHeight())
                            top_cor = env->getHeight() - 1;


                        for (int h = top_cor; h >= position.y + 1; --h) {
                            for (int w = left_cor; w <= right_cor; w++) {
                                std::cout << " { " << w << ", " << h << " } ";
                            }
                            std::cout << std::endl;
                        }

                        if (sens->getAngle() > 0) {
                            int bottom_cor = position.y - sens->getRadius();
                            if (bottom_cor < 0)
                                bottom_cor = 0;

                            for (int h = position.y; h >= bottom_cor; --h) {
                                for (int w = left_cor; w < position.x; ++w) {
                                    std::cout << " { " << w << ", " << h << " } ";
                                }
                                std::cout << std::endl;
                            }

                        }
                    }
                }
            }
        }
    }
}