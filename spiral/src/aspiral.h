#ifndef _A_SPIRAL_
#define _A_SPIRAL_
#include <math.h>

namespace aspiral {
	class Spiral {
	private: 
		double step;
	public:
		Spiral(double st = 1);
		Spiral& setStep(double st);
		double centerDist(double angle) const;
	};
}

#endif