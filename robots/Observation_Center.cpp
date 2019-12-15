#include "Observation_Center.h"
#include "Sensor.h"

namespace robo {
    Observation_Center::Observation_Center(unsigned int ports, unsigned int consumption, int price, std::vector<Module *> & mods,
                                           std::string & desc, coordinates pos) : Map_Object(pos), description(desc), cost(price), countPorts(ports), energyConsumption(consumption), appeared(true), owner(nullptr) {
        initModules(mods);
    }

    void Observation_Center::initModules(const std::vector<Module *> & modul) {
        if (countPorts < modul.size())
            throw std::invalid_argument("Robot has too many modules");

        for (auto itm : modul) {
            modules.push_back((*itm).copy());
        }
    }

    std::string Observation_Center::whoami() {
        std::stringstream ss;
        std::string host = owner != nullptr ? owner->getDescription() : "none";

        ss << "Object : Observation_Center: {" << position.x << ", " << position.y << "}\nDesc: '" << description << "';\n"
                                           "Consumption: " << energyConsumption << ";\nCost: " << cost << ";\n"
                                           "PortsCount: " << countPorts << ";\nAppeared: " << appeared << ";\nOwner = " << host << std::endl;
        ss << "Modules:\n" << myModules() << std::endl;
        return ss.str();
    }

    std::string Observation_Center::myModules() {
        std::stringstream ss;
        for (auto & mod : modules) {
            ss << mod->whoami() << std::endl;
        }

        return ss.str();
    }

    void Observation_Center::determineCorers(int & top_cor, int & left_cor, int & bottom_cor, int & right_cor, unsigned int rad) const {
        top_cor = position.y + rad;
        if (top_cor >= env->getHeight())
            top_cor = env->getHeight() - 1;

        left_cor = position.x - rad;
        if (left_cor < 0)
            left_cor = 0;

        bottom_cor = position.y - rad;
        if (bottom_cor < 0)
            bottom_cor = 0;

        right_cor = position.x + rad;
        if (right_cor >= env->getWidth())
            right_cor = env->getWidth() - 1;
    }

    std::map<coordinates, Map_Object *> Observation_Center::look() {
        std::map<coordinates, Map_Object *> one_view;
        for (auto & module : modules) {
            if(!strcmp(typeid(*module).name(), "N4robo6SensorE") && module->getActive()) {
                auto * sens = static_cast<robo::Sensor *>(module);

                //std::cout << "Active Senor rad = " << sens->getRadius() << " dir = " << sens->getDirection() << " angle = " << sens->getAngle() << std::endl;

                unsigned int real_dir = sens->getDirection(getDirection()); //if will be direction of robot
                //std::cout << real_dir << std::endl;

                int top_cor, left_cor, bottom_cor, right_cor;
                determineCorers(top_cor, left_cor, bottom_cor, right_cor, sens->getRadius());

                coordinates c_posit = getPosition(); //there may be interest point
                Map_Object * c_resp = env->checkStaticPoint(c_posit);
                one_view[c_posit] = c_resp;

                coordinates posit = {static_cast<unsigned int>(getX()), static_cast<unsigned int>(getY())};
                Map_Object * resp = env->checkStaticPoint(posit);
                one_view[posit] = resp;

                if (sens->getAngle() == 2) {
                    for (int h = top_cor; h >= bottom_cor && h <= top_cor; --h) {
                        for (int w = left_cor; w <= right_cor; ++w) {
                            if (getX() != w || getY() != h) {
                                //std::cout << " { " << w << ", " << h << " } ";
                                coordinates posit = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                                Map_Object * resp = env->checkStaticPoint(posit);
                                one_view[posit] = resp;
                            }
                        }
                        //std::cout << std::endl;
                    }
                }
                else {
                    if (real_dir == 0) { //top
                        for (int h = top_cor; h >= position.y + 1; --h) {
                            for (int w = left_cor; w <= right_cor; w++) {
                                //std::cout << " { " << w << ", " << h << " } ";
                                coordinates posit = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                                Map_Object * resp = env->checkStaticPoint(posit);
                                one_view[posit] = resp;
                            }
                            //std::cout << std::endl;
                        }

                        if (sens->getAngle() > 0) {
                            for (int h = position.y; h >= bottom_cor && h <= position.y; --h) {
                                for (int w = left_cor; w < position.x; ++w) {
                                    //std::cout << " { " << w << ", " << h << " } ";
                                    coordinates posit = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                                    Map_Object * resp = env->checkStaticPoint(posit);
                                    one_view[posit] = resp;
                                }
                                //std::cout << std::endl;
                            }

                        }
                    }
                    else if (real_dir == 1) { // left
                        for (int h = top_cor; h >= bottom_cor && h <= top_cor; --h) {
                            for (int w = left_cor; w < position.x; ++w) {
                                //std::cout << " { " << w << ", " << h << " } ";
                                coordinates posit = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                                Map_Object * resp = env->checkStaticPoint(posit);
                                one_view[posit] = resp;
                            }
                            //std::cout << std::endl;
                        }
                        //std::cout << std::endl;
                        if (sens->getAngle() > 0 && position.y != 0) {
                            for (int h = position.y-1; h >= bottom_cor && h <= position.y-1; --h) {
                                for (int w = position.x; w < right_cor; ++w) {
                                    //std::cout << " { " << w << ", " << h << " } ";
                                    coordinates posit = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                                    Map_Object * resp = env->checkStaticPoint(posit);
                                    one_view[posit] = resp;
                                }
                                //std::cout << std::endl;
                            }
                        }
                    }
                    else if (real_dir == 2) { //bottom
                        if(position.y != 0) {
                            for (int h = position.y-1; h >= bottom_cor && h <= position.y-1; --h) {
                                for (int w = left_cor; w <= right_cor; ++w) {
                                    coordinates posit = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                                    Map_Object * resp = env->checkStaticPoint(posit);
                                    one_view[posit] = resp;
                                }
                                //std::cout << std::endl;
                            }
                        }
                        //std::cout << std::endl;
                        if (sens->getAngle() > 0) {
                            for (unsigned int h = top_cor; h >= position.y && h <= top_cor; --h) {
                                for (unsigned int w = position.x+1; w <= right_cor; ++w) {
                                    std::cout << " { " << w << ", " << h << " } ";
                                    coordinates posit = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                                    Map_Object * resp = env->checkStaticPoint(posit);
                                    one_view[posit] = resp;
                                }
                                //std::cout << std::endl;
                            }
                        }
                    }
                    else { //right
                        for (int h = top_cor; h >= bottom_cor && h <= top_cor; --h) {
                            for (int w = position.x+1; w <= right_cor; ++w) {
                                //std::cout << " { " << w << ", " << h << " } ";
                                coordinates posit = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                                Map_Object * resp = env->checkStaticPoint(posit);
                                one_view[posit] = resp;
                            }
                            //std::cout << std::endl;
                        }
                    }

                    //std::cout << std::endl;
                    if (sens->getAngle() > 0) {
                        for (int h = top_cor; h > position.y && h <= top_cor; --h) {
                            for (int w = left_cor; w <= position.x; ++w) {
                                //std::cout << " { " << w << ", " << h << " } ";
                                coordinates posit = {static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
                                Map_Object * resp = env->checkStaticPoint(posit);
                                one_view[posit] = resp;
                            }
                            //std::cout << std::endl;
                        }
                    }
                }
            }
        }
        return one_view;
    }

    void Observation_Center::setOwner(Map_Object * own) {
        owner = static_cast<Observation_Center *>(own);
    }

    unsigned int Observation_Center::getMaxRadius() const {
        unsigned int maxr = 0;
        for (auto & module : modules) {
            if (!strcmp(typeid(*module).name(), "N4robo6SensorE")) {
                unsigned int curRad = dynamic_cast<Sensor *>(module)->getRadius();
                if (curRad > maxr) {
                    maxr = curRad;
                }
            }
        }

        return maxr;
    }

    void Observation_Center::determineCorers(int & top_cor, int & left_cor, int & bottom_cor, int & right_cor, unsigned int rad, coordinates pos) {
        top_cor = pos.y + rad;
        if (top_cor >= env->getHeight())
            top_cor = env->getHeight() - 1;

        left_cor = pos.x - rad;
        if (left_cor < 0)
            left_cor = 0;

        bottom_cor = pos.y - rad;
        if (bottom_cor < 0)
            bottom_cor = 0;

        right_cor = pos.x + rad;
        if (right_cor >= env->getWidth())
            right_cor = env->getWidth() - 1;
    }
}