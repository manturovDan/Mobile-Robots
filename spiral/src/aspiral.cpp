#include "aspiral.h"

namespace aspiral {
	Spiral::Spiral(double st) {
		if(st < 0)
			throw std::invalid_argument("Invalid step");
		this->step = st;
	}

	Spiral& Spiral::setStep(double st) {
		if(st < 0)
			throw std::invalid_argument("Invalid step");
		this->step = st;
		return *this;
	}

	double Spiral::areaOfSector(double fi1, double fi2) const {
		double p1 = Spiral::centerDist(fi1);
		double p2 = Spiral::centerDist(fi2);
		return abs(fi1 - fi2) * (p1*p1 + p1*p2 + p2*p2) / 6;
	}

	double Spiral::areaBefCoil(int n) const {
		return (n*n*n - (n-1)*(n-1)*(n-1)) * M_PI * (this->step) * (this->step) / 3;
	}

	double Spiral::areaOfCircle(int n) const {
		double s0 = Spiral::areaBefCoil(1);
		if(!n)
			return s0;
		return 6*n*s0;
	}

	double Spiral::curveLen(double fi) const {
		return (this->step) * (fi * sqrt(1 + fi*fi) + log(fi + sqrt(1 + fi*fi))) / (4 * M_PI);
	}

	double Spiral::curveRad(double fi) const {
		return (this->step) * (pow(fi*fi + 1, 1.5)/(fi*fi + 2)) / (2 * M_PI);
	}
}