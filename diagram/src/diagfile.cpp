#include <iostream>

#include "diagfile.h"

namespace fileD {
    int inpString(std::string &inp, const char *again, std::ostream &stream) {
        bool more = false;
        while (1) {
            if (more)
                std::cout << again << std::endl;

            std::cin >> inp;
            if (!std::cin.good()) {
                std::cin.clear();
                std::cin.ignore(100, '\n');
                more = 1;
                continue;
            }

            return 0;
        }
    }

    int readTextDiag(std::string & filename, timeD::Diagram &diag, std::ostream &stream) {
        std::string get_str;
        std::ifstream is;
        is.open(filename);
        if (is.is_open()) {
            std::getline(is, get_str);
            std::replace(get_str.begin(), get_str.end(), '_', '0');
            std::replace(get_str.begin(), get_str.end(), '-', '1');
            std::replace(get_str.begin(), get_str.end(), ' ', 'X');
            try {
                diag = timeD::Diagram(&get_str[0]);
            } catch (std::exception &ex) {
                stream << "File has incorrect diagram" << std::endl;
                return 1;
            }
            is.close();
        }
        else {
            stream << "File error" << std::endl;
            return 1;
        }

        stream << "The diagram has read" << std::endl;

        return 0;
    }
}