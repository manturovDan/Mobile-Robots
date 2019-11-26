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

            while (module != nullptr) {
                if (!strcmp(module->Name(), "Power_Generator")) {
                    std::cout << "POWER" << std::endl;
                    unsigned int production;
                    if (module->QueryUnsignedAttribute("production", &production) != 0) fileDamaged(stream, "getting production of pg");

                    auto prodm = new robo::Power_Generator()
                }

                module = module->NextSiblingElement();
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