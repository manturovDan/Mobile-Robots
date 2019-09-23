#include <iostream>

#include "aspiral.h"

int main() {
	aspiral::Spiral spir(1.8);

	std::cout << spir.getStep() << std::endl;

	return 0;
}
