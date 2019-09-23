#include "input.h"

namespace Input {
	int inpDbl(double &inp, bool unneg, const char *again) {
		bool more = false;
		int gnStatus;
		while (1) {
			if (more) 
				std::cout << again << std::endl;

			std::cin >> inp;
			if (!std::cin.good())
				return -1;
			if(std::abs(inp) > 100000000 || unneg && inp < 0)
				more = true;
			else 
				return 0;
		}
	}
}