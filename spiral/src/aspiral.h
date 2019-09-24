#ifndef _A_SPIRAL_
#define _A_SPIRAL_

#include <math.h>
#include <stdexcept>

namespace aspiral {
	class Spiral {
	private: 
		double step;
	public:
		Spiral(double st = 1);
		double getStep() const { return this->step; }
		Spiral& setStep(double);
		double centerDist(double angle) const { return abs((this->step)*angle/(2*M_PI)); }
		double areaOfSector(double, double) const;
		double areaBefCoil(int) const;
		double areaOfCircle(int) const;
		double curveLen(double) const;
		double curveRad(double) const;
	};
}

#endif