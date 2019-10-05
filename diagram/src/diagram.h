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
		static const int SZ = 100; //and max length of diagram
		signal interval[SZ];
		int length;
		int sigNum;
	public:
		Diagram(): length(0), sigNum(0) {}
		Diagram(char *, int);
		Diagram(char, int length=SZ);

		Diagram &addSignal(char, int, int);
		std::ostream &printDiagram(std::ostream&) const;
		std::ostream &printSignals(std::ostream&) const;

		Diagram &copyDiagram(const Diagram&);
		int uniDiagram(Diagram&);
		int copyDiagram(int, Diagram&);
		Diagram &rerlace(int, int, const Diagram&);
		Diagram &shiftRight(int, Diagram&);
		Diagram &shiftLeft(int, Diagram&);

		Diagram &setLength(int, Diagram&);
		int getLength() const { return length; }
		int getSigNum() const { return sigNum; }
	};
}

#endif