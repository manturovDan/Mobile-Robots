#include "diagram.h"

namespace timeD {
	Diagram & Diagram::addSignal(char symb, int start, int len) {
		if (start < length)
			throw std::invalid_argument("Incorrect start position");
		if (start + len > SZ)
			throw std::invalid_argument("Diagram is too big");

		int signal;

		if (len <= 0)
			return *this;

		if (symb == '0') {
			interval[sigNum].val = 0;
		} else if (symb == '1') {
			interval[sigNum].val = 1;
		} else if (symb == 'X') {
			length = start + len;
			return *this;
		} else {
			throw std::invalid_argument("Incorrect signal");
		}

		interval[sigNum].start = start;
		interval[sigNum].length = len;
		length = start + len;
		sigNum++;

		return *this;
	}

	std::ostream & Diagram::printDiagram(std::ostream& stream) const {
		int pos = 0;
		int signalEl = 0;
		stream << "Time\t0\t1" << std::endl;
		while (pos < length) {
			if (pos < interval[signalEl].start) {
				stream << pos << std::endl;
				pos++;
			} else {
				for(; pos < interval[signalEl].start + interval[signalEl].length; pos++) {
					if (interval[signalEl].val == 1)
						stream << pos << "\t\t|" << std::endl;
					else 
						stream << pos << "\t|\t" << std::endl;
				}
				signalEl++;
			}

		}
		return stream;
	}

	std::ostream & Diagram::printSignals(std::ostream& stream) const {
		stream << "length: " << length << std::endl;
		for (int i = 0; i < sigNum; i++) {
			stream << interval[i].val << " - " << interval[i].start << " - " << interval[i].length << std::endl;  
		}

		return stream;
	}
}