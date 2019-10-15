#ifndef T_DIAGRAM
#define T_DIAGRAM

#include <iostream>
#include <exception>
#include <string.h>

namespace timeD {
    struct signal {
        bool val;
        int start;
        int length;
    };

    class Diagram {
    private:
        static const int SZlen = 100; //and max length of diagram
        static const int SZsig = 100;
        signal interval[SZsig];
        int length;
        int sigNum;
    public:
        Diagram(): length(0), sigNum(0) {}
        Diagram(const char *);
        Diagram(char symb): length(0), sigNum(0) { addSignal(symb, 0, SZlen); }

        Diagram &addSignal(char, int, int);
        std::ostream &printDiagram(std::ostream&) const;
        std::ostream &printSignals(std::ostream&) const;

        int operator += (const Diagram&);
        Diagram operator ++ ();
        Diagram operator ++ (int);
        Diagram operator + (const Diagram &);
        int operator << (int);
        int operator >> (int);

        int copyDiagram(int);
        int cutDiag(int);
        Diagram &replace(int, const Diagram&);
        int shift(int);

        int getLength() const { return length; }
        int getSigNum() const { return sigNum; }
        int getSZlen() const { return SZlen; }
        int getSZsig() const { return SZsig; }
        int getSig(int num) { return interval[num].val; }
        int getSigStart(int num) { return interval[num].start; }
        int getSigLen(int num) { return interval[num].length; }	};
}

#endif