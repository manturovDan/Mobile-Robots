#ifndef T_DIAGRAM
#define T_DIAGRAM

#include <iostream>
#include <exception>
#include <cstring>
#include <iomanip>

//version 3

namespace timeD {
    struct signal {
        bool val;
        int start;
        int length;
    };

    class Diagram {
    private:
        static const int maxLen = 10e3; //TODO recalculate
        static const int maxSig = 10e3;
        static const int magnifier = 10; //number on which vector increases all the time
        signal *interval;
        int length;
        int sigNum;
        int scale; //count og magnifiers
    public:
        Diagram(): length(0), sigNum(0), scale(1), interval(new signal[magnifier]) {}
        Diagram(const char *);
        Diagram(char symb): length(0), sigNum(0), scale(1), interval(new signal[magnifier]) { addSignal(symb, 0, maxLen); }
        Diagram(const Diagram &);
        Diagram(Diagram &&);
        //~Diagram() { delete[] interval; };

        Diagram & operator =(const Diagram &);
        Diagram & operator =(Diagram &&);
        Diagram& operator += (const Diagram&); // A+=B+=C;
        Diagram & operator ++ (); // ++ ++ A;
        Diagram operator ++ (int);
        Diagram & operator << (int);
        Diagram & operator >> (int);

        Diagram &addSignal(char, int, int);
        std::ostream &printDiagram(std::ostream&) const;
        std::ostream &printSignals(std::ostream&) const;

        friend std::ostream & operator << (std::ostream &, const Diagram &);
        friend std::istream & operator >> (std::istream &, Diagram &);
        friend Diagram operator + (const Diagram &, const Diagram &);
        int operator () ( int,  int, Diagram &);

        int copyDiagram(int);
        int cutDiag(int);
        Diagram &replace(int, const Diagram&);
        int shift(int);

        int getLength() const { return length; }
        int getSigNum() const { return sigNum; }
        int getScale() const { return scale; }
        int getMaxLen() const { return maxLen; }
        int getSig(int num) { return interval[num].val; } //сделать проверку и char TODO
        int getSigStart(int num) { return interval[num].start; }
        int getSigLen(int num) { return interval[num].length; }	};
}

#endif