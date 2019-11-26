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
            unsigned int x;
            unsigned int y;

            if (mapEl->QueryUnsignedAttribute("x", &x) != 0) fileDamaged(stream, "getting x"); //must be absented in robots
            if (mapEl->QueryUnsignedAttribute("y", &y) != 0) fileDamaged(stream, "getting y");
            if (x >= width || y >= height) fileDamaged(stream, "incorrect x y");

            stream << mapEl->Name() << std::endl;

            robo::coordinates pos = {x, y};

            bool is_robo = true;
            bool is_commander = false;

            if (!strcmp(mapEl->Name(), "Obstacle")) {
                env.setObject(pos, robo::Obstacle_t);
                is_robo = false;
            } else if (!strcmp(mapEl->Name(), "Interest")) {
                env.setObject(pos, robo::Interest_t);
                is_robo = false;
            } else if (!strcmp(mapEl->Name(), "Command_Center")) {
                env.setObject(pos, robo::Command_Center_t);
                is_commander = true;
            } else if (!strcmp(mapEl->Name(), "Robot_Commander")) {
                is_commander = true;
                env.setObject(pos, robo::Robot_Commander_t);
            } else if (!strcmp(mapEl->Name(), "Observation_Center")) {
                env.setObject(pos, robo::Observation_Center_t);
            } else if (!strcmp(mapEl->Name(), "Robot_Scout")) {
                env.setObject(pos, robo::Robot_Scout_t);
            }


            if (is_robo) {
                tinyxml2::XMLElement * module = mapEl->FirstChildElement();

                while (module != nullptr) {
                    if (!strcmp(mapEl->Name(), "Power_Generator")) {

                    }

                    module = module->NextSiblingElement();
                }
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