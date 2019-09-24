#include <iostream>

#include "aspiral.h"

template <class T>
int inpNum(T &inp, bool unneg = false, const char *again = "Input error! Try again!") {
	bool more = false;
	int gnStatus;
	while (1) {
		if (more) 
			std::cout << again << std::endl;

		std::cin >> inp;
		if (!std::cin.good())
			throw std::invalid_argument("Invalid input");
		if(std::abs(inp) > 100000000 || unneg && inp < 0)
			more = true;
		else 
			return 0;
	}
}

int chooseNum() {
	int choise;
	while (1) {
		std::cout<<"Choose the number:\n\
	1. Get distance to origin by angle\n\
	2. Get area of secotor between two angles <= 2*π\n\
	3. Get area of figure limited by n-th coil\n\
	4. Get area of n-th circle\n\
	5. Get length of arc to before given angle\n\
	6. Get radius of curvature depending on the angle" << std:: endl;	
		
		inpNum(choise);
		if(choise >= 1 && choise <= 6)
			return choise;

		std::cout << "Incorrect value!" << std::endl;

	}
}

void distToCenter(aspiral::Spiral& spir) {
	double fi;
	std::cout << "Input the angle to calculate the distance to origin:" << std::endl;
	inpNum(fi);
	std::cout << "Result: " << spir.centerDist(fi) << std::endl;
}

void secArea(aspiral::Spiral& spir) {
	double f1, f2;
	while (1) {
		std::cout << "Input two angles with one sign (not bigger than 2*π)\nInput the first:" << std::endl;
		inpNum(f1);
		std::cout << "Input the second:" << std::endl;
		inpNum(f2);

		if (abs(f1) > 2 * M_PI || abs(f2) > 2 * M_PI) {
			std::cout << "Input angles not bigger tnan 2*π" << std::endl;
			continue;
		}
		else if (f1 <= 0 && f2 <= 0 || f1 >= 0 & f2 >= 0) {
			std::cout << "Result: " << spir.areaOfSector(f1, f2) << std::endl;
			return;
		}
		else {
			std::cout << "Input angles with the same sign" << std::endl;
		}
	}
}


void coilArea(aspiral::Spiral& spir) {
	int n;
	std::cout << "Input number of limiting coil:" << std::endl;
	inpNum(n, 1);
	std::cout << "Result: " << spir.areaBefCoil(n) << std::endl;
}

void circleArea(aspiral::Spiral& spir) {
	int n;
	std::cout << "Input number of circle:" << std::endl;
	inpNum(n, 1);
	std::cout <<"Result: " << spir.areaOfCircle(n) << std::endl;
}

void lenCurve(aspiral::Spiral& spir) {
	double fi;
	std::cout << "Input angle:" << std::endl;
	inpNum(fi);
	std::cout << "Result: " << spir.curveLen(fi) << std::endl;
}

void curRad(aspiral::Spiral& spir) {
	double fi;
	std::cout << "Input angle:" << std::endl;
	inpNum(fi);
	std::cout << "Result: " << spir.curveRad(fi) << std::endl;	
}

int main() {
	aspiral::Spiral spir;
	int interface;
	std::cout << "Default spiral (step = 1) has created" << std::endl;
	while (1) {
		std::cout << "Choose the option: \n1 - to set Spiral\n2 - to continue with current spiral\n0 - to exit" << std::endl;
		inpNum(interface);

		if (interface == 0)
			break;

		if (interface == 1)
		{
			double step;
			std::cout << "The equation of Archimedean spiral in polar coordinates is ρ=(a*φ/(2*π)),\
			 where ρ is the distance, a is the step, φ is the angle\nInput step:" << std::endl;
			inpNum(step, 1);
			spir.setStep(step);
		}

		int choise = chooseNum();
		switch(choise) {
			case 1:
				//dist by fi
				distToCenter(spir);
				break;
			case 2:
				//area <> 2 ang
				secArea(spir);
				break;
			case 3:
				//n area
				coilArea(spir);
				break;
			case 4:
				//circle area
				circleArea(spir);
				break;
			case 5:
				//length
				lenCurve(spir);
				break;
			case 6:
				//radius curve
				curRad(spir);
				break;
		}


	}

	std::cout << "The end!" << std::endl;
	return 0;
}
