#include "interface.h"

namespace interf {
    EnvXMLCreate::EnvXMLCreate(const std::string & filename , robo::Environment_describer & env, std::ostream & stream) {
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError eResult = doc.LoadFile(&filename[0]);

        if (eResult != 0) {
            stream << "Error of file access" << std::endl;
            throw std::invalid_argument("file access error");
        }

        tinyxml2::XMLElement * pEnv = doc.FirstChildElement();
        if (pEnv == nullptr)
            fileDamaged(stream);

        unsigned int width;
        unsigned int height;

        if (pEnv->QueryUnsignedAttribute("width", &width) != 0) fileDamaged(stream, "getting width");
        if (pEnv->QueryUnsignedAttribute("height", &height) != 0) fileDamaged(stream, "getting height");

        env.setWidth(width);
        env.setHeight(height);

        tinyxml2::XMLElement * mapEl = pEnv->FirstChildElement();

        while (mapEl != nullptr) {

            stream << mapEl->Name() << std::endl;

            tinyxml2::XMLElement * module = mapEl->FirstChildElement();

            std::vector<robo::Module *> modl;

            robo::Module * mod;

            while (module != nullptr) {
                int priority;
                if (module->QueryIntAttribute("priority", &priority) != 0) fileDamaged(stream, "getting priority of pg");

                if (!strcmp(module->Name(), "Power_Generator")) {
                    std::cout << "POWER" << std::endl;
                    unsigned int production;

                    if (module->QueryUnsignedAttribute("production", &production) != 0) fileDamaged(stream, "getting production of pg");

                    mod = new robo::Power_Generator(priority, production);

                } else if (!strcmp(module->Name(), "Sensor")) {
                    std::cout << "SENSOR" << std::endl;

                    unsigned int consumption, radius, direction, angle;

                    if (module->QueryUnsignedAttribute("consumption", &consumption) != 0) fileDamaged(stream, "getting consumption of sensor");
                    if (module->QueryUnsignedAttribute("radius", &radius) != 0) fileDamaged(stream, "getting radius of sensor");
                    if (module->QueryUnsignedAttribute("direction", &direction) != 0) fileDamaged(stream, "getting direction of sensor");
                    if (module->QueryUnsignedAttribute("angle", &angle) != 0) fileDamaged(stream, "getting angle of sensor");

                    mod = new robo::Sensor(radius, direction, angle, consumption, priority);
                }
                else if (!strcmp(module->Name(), "Managing")) {
                    std::cout << "MAN_MODULE" << std::endl;

                    unsigned int consumption, radius, subs;

                    if (module->QueryUnsignedAttribute("consumption", &consumption) != 0) fileDamaged(stream, "getting consumption of maneging module");
                    if (module->QueryUnsignedAttribute("radius", &radius) != 0) fileDamaged(stream, "getting radius of maneging module");
                    if (module->QueryUnsignedAttribute("subordinates_count", &subs) != 0) fileDamaged(stream, "getting subordinates count of maneging module");

                    mod = new robo::Managing(radius, consumption, priority, subs);

                }
                else {
                    throw std::invalid_argument("Robot has unknown module");
                }

                modl.push_back(mod);

                module = module->NextSiblingElement();
            }

            unsigned int x, y, ports, consumption, speed;
            int price;
            const char * robo_desc;
            std::string desc;

            bool are_coord = false;
            bool is_robot = false;
            bool is_speed = false;
            robo::coordinates pos {0, 0};

            if (mapEl->QueryUnsignedAttribute("x", &x) == 0 && mapEl->QueryUnsignedAttribute("y", &y) == 0) {
                are_coord = true;
                pos = {x, y};
            }

            if (mapEl->QueryUnsignedAttribute("consumption", &consumption) == 0 && mapEl->QueryUnsignedAttribute("ports", &ports) == 0
            && mapEl->QueryIntAttribute("price", &price) == 0 && mapEl->QueryStringAttribute("description", &robo_desc) == 0) {
                is_robot = true;
                desc = robo_desc;
            }

            if (mapEl->QueryUnsignedAttribute("speed", &speed) == 0) {
                is_speed = true;
            }

            robo::Map_Object *prod;

            if (!strcmp(mapEl->Name(), "Obstacle")) {
                if (are_coord)
                    prod = env.setObject(robo::Obstacle_t, pos);
                else
                    throw std::invalid_argument("Not coordinates for obstacle object");
            } else if (!strcmp(mapEl->Name(), "Interest")) {
                if (are_coord)
                    prod = env.setObject(robo::Interest_t, pos);
                else
                    throw std::invalid_argument("Not coordinates for interest point");
            } else if (!strcmp(mapEl->Name(), "Observation_Center")) {
                if (are_coord && is_robot) {
                    prod = env.setObject(robo::Observation_Center_t, ports, consumption, price, modl, desc, pos);
                }
                else
                    throw std::invalid_argument("Not enough data for Observation Center");
            } else if (!strcmp(mapEl->Name(), "Command_Center")) {
                if (are_coord && is_robot) {
                    prod = env.setObject(robo::Command_Center_t, ports, consumption, price, modl, desc, pos);
                }
                else
                    throw std::invalid_argument("Not enough data for Command Center");
            } else if (!strcmp(mapEl->Name(), "Robot_Commander")) {
                if (is_speed && is_robot) {
                    prod = env.setObject(robo::Robot_Commander_t, ports, consumption, price, modl, desc, speed);
                }else
                    throw std::invalid_argument("Not enough data for Robot Commander");
            } else if (!strcmp(mapEl->Name(), "Robot_Scout")) {
                if (is_speed && is_robot) {
                    prod = env.setObject(robo::Robot_Scout_t, ports, consumption, price, modl, desc, speed);
                }else
                    throw std::invalid_argument("Not enough data for Robot Scout");
            }
            else {
                throw std::invalid_argument("Unknown object on the map");
            }

            mapEl = mapEl->NextSiblingElement();
        }

        env.print();

    }

    void EnvXMLCreate::fileDamaged(std::ostream & stream = std::cout, const std::string & add) {
        stream << "File was damaged! - " << add << std::endl;
        throw std::invalid_argument("file error");
    }

    void InterfaceTools::printEnv(std::ostream &stream) {
        stream << "Width: " << env->getWidth() << " Height: " << env->getHeight() << std::endl;
        stream << "DEBUG - printing all objects:" << std::endl;
        unsigned int number = 0;
        for (auto it = env->begin(); it != env->end(); ++it) {
            std::cout << (++number) << " --- OBJECT - " << typeid(*(*it)).name() << std::endl;
            std::cout << (*it)->whoami() << std::endl;
        }
    }
}