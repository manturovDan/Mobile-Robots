#ifndef ROBOTS_INTERFACE_H
#define ROBOTS_INTERFACE_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "../libraries/tinyxml2-lib/tinyxml2.h"

#include "robot.h"

namespace interf {
    /// Class that creates Environment from XML FILE
    class EnvXMLCreate {
    public:
        EnvXMLCreate() = delete;

        ///@param std::string path - path of XML file
        EnvXMLCreate(const std::string &, robo::Environment_describer &, std::ostream & stream = std::cout);

    private:
        static void fileDamaged(std::ostream &, const std::string & add = "unknown");
    };
}

#endif //ROBOTS_INTERFACE_H
