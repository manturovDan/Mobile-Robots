#include <stdexcept>

#include "aspiral.h"

namespace aspiral {
	Spiral::Spiral(double st) {
		if(st < 0)
			throw std::invalid_argument("Invalid step");
		this->step = st;
	}

	double Spiral::areaOfSector(double fi1, double fi2) const {
		return abs(fi1 - fi2) * (fi1 * fi1 + fi1 * fi2 + fi2 * fi2) / 6;
	}
}