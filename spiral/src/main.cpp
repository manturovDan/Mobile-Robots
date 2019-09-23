#include <iostream>

#include "aspiral.h"
#include "input.h"

int main() {
	aspiral::Spiral spir;
	double interface;
	while (1) {
		std::cout << "Input \n1 - to set Spiral\n2 - to exit" << std::endl;
		if (Input::inpDbl(interface) < 0) {
			std::cout << "Stdin error" << std::endl;
			return -1;
		}

		if (interface == 1.)
		{
			double step;
			std::cout << "The equation of Archimedean spiral in polar coordinates is ρ=(a*φ/(2*π)),\
			 where ρ is the distance, a is the step, φ is the angle\nInput step:" << std::endl;
			if (Input::inpDbl(step, 1) < 0) {
				std::cout << "Stdin error" << std::endl;
				return -1;
			}
			spir.setStep(step);

			std::cout<<"Choose the number:\n\
1. Get distance to origin by angle\n\
2. Get area between two sectors (angles <= 2*π)\n\
3. Get area of figure limited by n-th coil\n\
4. Get area of n-th circle\n\
5. Get length of arc to before given angle\n\
6. Get radius of curvature depending on the angle" << std:: endl;
			std::cout << spir.getStep() << std::endl;
		}
		else if (interface == 2.)
			break;
	}

	return 0;
}
