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

            if (mapEl->QueryUnsignedAttribute("x", &x) != 0) fileDamaged(stream, "getting x");
            if (mapEl->QueryUnsignedAttribute("y", &y) != 0) fileDamaged(stream, "getting y");
            if (x >= width || y >= height) fileDamaged(stream, "incorrect x y");

            stream << mapEl->Name() << std::endl;

            robo::coordinates pos = {x, y};
            if (!strcmp(mapEl->Name(), "Obstacle")) {
                env.setObject(pos, robo::Obstacle_t);
            } else if (!strcmp(mapEl->Name(), "Interest")) {
                env.setObject(pos, robo::Interest_t);
            }

            mapEl = mapEl->NextSiblingElement();
        }

    }

    void EnvXMLCreate::fileDamaged(std::ostream & stream = std::cout, const std::string & add) {
        stream << "File was damaged! - " << add << std::endl;
        throw std::invalid_argument("file error");
    }
}