#include <iostream>

#include "diagram.h"

int main() {
	std::cout<<"Hello"<<std::endl;
	timeD::Diagram diag1;
	std::cout << diag1.getLength() <<std::endl;
	diag1.addSignal('1', 5, 3);
	diag1.addSignal('0', 8, 4);
	diag1.addSignal('0', 12, 4);
	diag1.addSignal('X', 16, 8);
	std::cout << diag1.getLength() <<std::endl;
	std::cout << diag1.getSigNum() <<std::endl;
	diag1.printDiagram(std::cout);
	diag1.printSignals(std::cout);

	timeD::Diagram diag2;
	diag2.addSignal('1', 0, 1);
	diag2.addSignal('1', 1, 2);
	diag2.addSignal('X', 3, 2);
	diag2.addSignal('0', 5, 3);

	diag2.printDiagram(std::cout);
	diag2.printSignals(std::cout);

	diag1.uniDiagram(diag2);
	std::cout << "United" << std::endl;
	diag1.printDiagram(std::cout);
	diag1.printSignals(std::cout);

	diag1.copyDiagram(3);
	diag1.printDiagram(std::cout);
	diag1.printSignals(std::cout);


}