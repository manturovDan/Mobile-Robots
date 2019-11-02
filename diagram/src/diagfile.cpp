#include <iostream>
#include <jmorecfg.h>

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

    int writeTextDiag(std::string & filename, timeD::Diagram &diag, std::ostream &stream) {
        std::ofstream os;
        os.open(filename);

        int pos = 0;
        int signalEl = 0;
        while (pos < diag.getLength()) {
            if (signalEl >= diag.getSigNum() || pos < diag.getSigStart(signalEl)) {
                os << ' ';
                pos++;
            } else {
                for(; pos < diag.getSigStart(signalEl) + diag.getSigLen(signalEl); pos++) {
                    if (diag.getSig(signalEl) == 1)
                        os << '_';
                    else {
                        os << '-';
                    }
                }
                signalEl++;
            }
        }
        os << std::endl;

        stream << "The diagram has wrote" << std::endl;
        return 0;
    }

    int writeBinary(std::string & filename, timeD::Diagram &diag, std::ostream &stream) {
        std::ofstream os(filename, std::ios::binary | std::ios::out);
        if (!os) {
            stream << "Cannot open file!" << std::endl;
            return 1;
        }

        timeD::signal *sgns = new timeD::signal[diag.getSigNum()];
        for (int i = 0; i < diag.getSigNum(); ++i) {
            sgns[i] = { bool(diag.getSig(i)), diag.getSigStart(i), diag.getSigLen(i) };
        }

        int length = diag.getLength();
        int sigNums = diag.getSigNum();

        //os.write((char *) &length, sizeof(length));
        //os.write((char *) &sigNums, sizeof(length));
        os << length << sigNums <<std::endl;

        os << std::endl;
        delete[] sgns;
    }

    int readBinary(std::string & filename, timeD::Diagram &diag, std::ostream &stream) {
        std::ifstream is(filename, std::ios::binary | std::ios::out);
        if (!is) {
            stream << "Cannot open file!" << std::endl;
            return 1;
        }

        int length;
        int sigNums;
        is >> length >> sigNums;
        stream << length << ' ' << sigNums << std::endl;

        return 0;
    }

    int writeXML(std::string & filename, timeD::Diagram &diag, std::ostream &stream) {
        tinyxml2::XMLDocument doc;

        tinyxml2::XMLNode * pRoot = doc.NewElement("Diagram");
        doc.InsertFirstChild(pRoot);

        tinyxml2::XMLElement * pLength = doc.NewElement("Length");
        pLength->SetText(diag.getLength());
        pRoot->InsertEndChild(pLength);

        tinyxml2::XMLElement * pSignals = doc.NewElement("Signals");
        pSignals->SetText(diag.getSigNum());
        pRoot->InsertEndChild(pSignals);
        if (diag.getSigNum() > 0) {
            tinyxml2::XMLElement *pSuccession = doc.NewElement("Succession");

            doc.InsertFirstChild(pSuccession);
            for (int i = 0; i < diag.getSigNum(); ++i) {
                tinyxml2::XMLElement *pSig = doc.NewElement("Sig");
                doc.InsertFirstChild(pSig);

                tinyxml2::XMLElement *pVal = doc.NewElement("Val");
                pVal->SetText(diag.getSig(i));
                pSig->InsertEndChild(pVal);

                tinyxml2::XMLElement *pStart = doc.NewElement("Start");
                pStart->SetText(diag.getSigStart(i));
                pSig->InsertEndChild(pStart);

                tinyxml2::XMLElement *pLen = doc.NewElement("Len");
                pLen->SetText(diag.getSigLen(i));
                pSig->InsertEndChild(pLen);

                pSuccession->InsertEndChild(pSig);
            }

            pRoot->InsertEndChild(pSuccession);
        }

        tinyxml2::XMLError eResult = doc.SaveFile(&filename[0]);
        if (eResult != 1 && eResult != 0)
        {
            stream << "File writing error!" << std::endl;
            return 1;
        }

        stream << "Correct writing" << std::endl;
        return 0;
    }

    int fileDamaged(std::ostream &stream) {
        stream << "Error. File was damaged!" << std::endl;
        return 1;
    }

    int readXML(std::string & filename, timeD::Diagram &diag, std::ostream &stream) {
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError eResult = doc.LoadFile(&filename[0]);
        if (eResult != 0) {
            stream << "Error of file access!" << std::endl;
            return 1;
        }

        tinyxml2::XMLNode * pDiag = doc.FirstChild();
        if (pDiag == nullptr) { stream << "ERROR1" <<std::endl; return fileDamaged(stream); }

        tinyxml2::XMLElement * pLength = pDiag->FirstChildElement("Length");
        if (pLength == nullptr) { stream << "ERROR2" <<std::endl; return fileDamaged(stream); }

        int length;
        eResult = pLength->QueryIntText(&length);
        if (eResult != 0) { stream << "ERROR3" <<std::endl; return fileDamaged(stream); }

        int sigNum;
        eResult = pLength->QueryIntText(&sigNum);
        if (eResult != 0) { stream << "ERROR4" <<std::endl; return fileDamaged(stream); }



        stream << length << std::endl;

        return 0;
    }
}