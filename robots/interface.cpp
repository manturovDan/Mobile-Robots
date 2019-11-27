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
                if (pEnv->QueryIntAttribute("priority", &priority) != 0) fileDamaged(stream, "getting priority of pg");

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

                    unsigned int consumption, radius;

                    if (module->QueryUnsignedAttribute("consumption", &consumption) != 0) fileDamaged(stream, "getting consumption of maneging module");
                    if (module->QueryUnsignedAttribute("radius", &radius) != 0) fileDamaged(stream, "getting radius of maneging module");

                    mod = new robo::Managing(radius, consumption, priority);

                }
                else {
                    throw std::invalid_argument("Robot has unknown module");
                }

                modl.push_back(mod);

                module = module->NextSiblingElement();
            }

            //make calling constructorrs of robots
            unsigned int x, y;

            if (mapEl->QueryUnsignedAttribute("x", &x) == 0 && mapEl->QueryUnsignedAttribute("y", &y) == 0) {

            }

            robo::coordinates pos = {x, y};

            bool is_robo = true;
            bool is_commander = false;
            robo::Map_Object *prod;

            if (!strcmp(mapEl->Name(), "Obstacle")) {
                prod = env.setObject(pos, robo::Obstacle_t);
                is_robo = false;
            } else if (!strcmp(mapEl->Name(), "Interest")) {
                prod = env.setObject(pos, robo::Interest_t);
                is_robo = false;
            } else if (!strcmp(mapEl->Name(), "Command_Center")) {
                prod = env.setObject(pos, robo::Command_Center_t);
                is_commander = true;
            } else if (!strcmp(mapEl->Name(), "Robot_Commander")) {
                prod = env.setObject(pos, robo::Robot_Commander_t);
                is_commander = true;
            } else if (!strcmp(mapEl->Name(), "Observation_Center")) {
                prod = env.setObject(pos, robo::Observation_Center_t);
            } else if (!strcmp(mapEl->Name(), "Robot_Scout")) {
                prod = env.setObject(pos, robo::Robot_Scout_t);
            }
            else {
                throw std::invalid_argument("Unknown object on the map");
            }


            if (is_robo) {
                std::cout << "ROBO" << std::endl;

            }

            mapEl = mapEl->NextSiblingElement();
        }

        env.print();

    }

    void EnvXMLCreate::fileDamaged(std::ostream & stream = std::cout, const std::string & add) {
        stream << "File was damaged! - " << add << std::endl;
        throw std::invalid_argument("file error");
    }
}