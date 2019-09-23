#include <stdexcept>

#include "aspiral.h"

namespace aspiral {
	Spiral::Spiral(double st) {
		if(st < 0)
			throw std::invalid_argument("Invalid step");
		this->step = st;
	}
}