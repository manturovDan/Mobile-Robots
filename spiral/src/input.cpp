#include <stdexcept>

#include "input.h"

namespace Input {
	template <class T>
	int inpNum(T &inp, bool unneg, const char *again) {
		bool more = false;
		int gnStatus;
		while (1) {
			if (more) 
				std::cout << again << std::endl;

			std::cin >> inp;
			if (!std::cin.good())
				throw "Invalid input";
			if(std::abs(inp) > 100000000 || unneg && inp < 0)
				more = true;
			else 
				return 0;
		}
	}
}