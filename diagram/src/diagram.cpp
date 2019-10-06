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

		bool sigVal;

		if (symb == '0') {
			sigVal = 0;
		} else if (symb == '1') {
			sigVal = 1;
		} else if (symb == 'X') {
			length = start + len;
			return *this;
		} else {
			throw std::invalid_argument("Incorrect signal");
		}

		if (interval[sigNum-1].val == sigVal && interval[sigNum-1].start + interval[sigNum-1].length == start) {
			interval[sigNum-1].length += len;
		} else {
			interval[sigNum].val = sigVal;
			interval[sigNum].start = start;
			interval[sigNum].length = len;
			sigNum++;
		}

		length = start + len;

		return *this;
	}

	int Diagram::uniDiagram(const Diagram &conc) {
		if (length + conc.length > SZ)
			return 1;

		for (int i = 0; i < conc.sigNum; ++i) {
			interval[sigNum + i].val = conc.interval[i].val;
			interval[sigNum + i].start = conc.interval[i].start + length;
			interval[sigNum + i].length = conc.interval[i].length;
		}

		length += conc.length;
		sigNum += conc.sigNum;

		return 0;
	}

	int Diagram::copyDiagram(int count) {
		if (length * count > SZ)
			return 1;

		for (int sig = 0; sig < sigNum; sig++) {
			for (int i = 1; i < count; i++) {
				interval[sigNum*i + sig].val = interval[sig].val;
				interval[sigNum*i + sig].start = interval[sig].start + length*i;
				interval[sigNum*i + sig].length = interval[sig].length;
			}
		}

		length *= count;
		sigNum *= count;

		return 0;
	}

	int Diagram::cutDiag(int moment) {
		int sig;

		for (sig = 0; sig < sigNum; ++sig) {
			if(interval[sig].start + interval[sig].length > moment) { //start of next signal
				if (interval[sig].start < moment) {
					interval[sig].length = moment - interval[sig].start;
					sigNum = sig + 1;
					length = moment;
				}
				else { //cutting in X, nothing to change
					sigNum = sig;
					length = moment;
				}
				return 0;
			}
		}

		if (moment >= length)
			return 1;
		else {
			length = moment;
		}
	}

	Diagram &Diagram::replace(int moment, const Diagram &add) {
		int cutLeft = (*this).Diagram::cutDiag(moment);
		if (cutLeft == 1)
			throw std::invalid_argument("Incorrect position");

		int sigAdd;
		for (sigAdd = 0; sigAdd < add.sigNum; ++sigAdd) {
			if (add.interval[sigAdd].start + add.interval[sigAdd].length > moment) {
				if (add.interval[sigAdd].start <= moment) {
					interval[sigNum].val = add.interval[sigAdd].val;
					interval[sigNum].start = moment;
					interval[sigNum].length = add.interval[sigAdd].start + add.interval[sigAdd].length - moment;
				}
				else {
					interval[sigNum].val = add.interval[sigAdd].val;
					interval[sigNum].start = add.interval[sigAdd].start;
					interval[sigNum].length = add.interval[sigAdd].length;
				}

				length = interval[sigNum].start + interval[sigNum].length;
				sigNum++;
				
			}
		}

		return *this;
	}

	int Diagram::shift(int times) {
		for (int sig = 0; sig < sigNum; ++sig) {
			interval[sig].start += times;
		}

		length += times;

		if (length > SZ) {
			for (int sig = sigNum-1; sig >= 0; --sig) {
				if (interval[sig].start < SZ) {
					sigNum = sig + 1;
					length = SZ;
					if (interval[sig].start + interval[sig].length > SZ) {
						interval[sig].length = SZ - interval[sig].start;
					}

					return 0;
				}
			}

			length = SZ;
			sigNum = 0;

		}
		else if (interval[0].start < 0) {
			for (int sig = 0; sig < sigNum; ++sig) {
				if (interval[sig].start + interval[sig].length > 0) {
					std::cout << sig << std::endl;
					if (interval[sig].start < 0) {
						interval[sig].length += interval[sig].start;
						interval[sig].start = 0;
					}

					for (int i = sig; i < sigNum; ++i) {
						interval[i - sig].val = interval[i].val;
						interval[i - sig].start = interval[i].start;
						interval[i - sig].length = interval[i].length;
					}

					sigNum -= sig;

					return 0;
				}
			}

			length = 0;
			sigNum = 0;
		}

		return 0;
	}

	std::ostream & Diagram::printDiagram(std::ostream& stream) const {
		int pos = 0;
		int signalEl = 0;
		stream << "Time\t0\t1" << std::endl;
		while (pos < length) {
			if (signalEl >= sigNum || pos < interval[signalEl].start) {
				stream << pos << std::endl;
				pos++;
			} else {
				for(; pos < interval[signalEl].start + interval[signalEl].length; pos++) {
					if (interval[signalEl].val == 1)
						stream << pos << "\t\t|" << std::endl;
					else {
						stream << pos << "\t|\t" << std::endl;
					}
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