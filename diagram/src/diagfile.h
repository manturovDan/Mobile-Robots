#ifndef DIAGRAM_DIAGFILE_H
#define DIAGRAM_DIAGFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "../tinyxml2-lib/tinyxml2.h"

#include "diagram.h"

namespace fileD {
    int inpString(std::string &inp, const char *again = "Input error! Try again!", std::ostream &stream = std::cout);
    int readTextDiag(std::string & , timeD::Diagram &, std::ostream &stream = std::cout);
    int writeTextDiag(std::string & , timeD::Diagram &, std::ostream &stream = std::cout);
    int writeBinary(std::string & , timeD::Diagram &, std::ostream &stream = std::cout);
    int readBinary(std::string & , timeD::Diagram &, std::ostream &stream = std::cout);
    int writeXML(std::string & , timeD::Diagram &, std::ostream &stream = std::cout);
}
#endif //DIAGRAM_DIAGFILE_H
