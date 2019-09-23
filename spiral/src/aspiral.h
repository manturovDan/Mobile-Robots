#ifndef _A_SPIRAL_
#define _A_SPIRAL_
#include <math.h>

namespace aspiral {
	class Spiral {
	private: 
		double step;
	public:
		Spiral(double st = 1);
		double getStep() const { return this->step; }
		Spiral& setStep(double st) { this->step = st; return *this; }
		//double centerDist(double angle) const { return (this->step)*angle/(2*M_PI) };
	};
}

#endif