#ifndef DIAGRAM_DIAGFILE_H
#define DIAGRAM_DIAGFILE_H

#include <fstream>
#include <string>
#include <algorithm>

#include "diagram.h"

namespace fileD {
    int inpString(std::string &inp, const char *again = "Input error! Try again!", std::ostream &stream = std::cout);
    int readTextDiag(std::string & , timeD::Diagram &, std::ostream &stream = std::cout);
    int writeTextDiag(std::string & , timeD::Diagram &, std::ostream &stream = std::cout);
}
#endif //DIAGRAM_DIAGFILE_H
