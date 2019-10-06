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

	timeD::Diagram diag2;
	diag2.addSignal('1', 0, 1);
	diag2.addSignal('1', 1, 2);
	diag2.addSignal('X', 3, 2);
	diag2.addSignal('0', 5, 3);

	//diag2.printDiagram(std::cout);
	//diag2.printSignals(std::cout);

	diag1.uniDiagram(diag2);
	diag1.addSignal('X', 32, 8);

	//diag1.printDiagram(std::cout);
	diag1.printSignals(std::cout);

	diag2.addSignal('0', 10, 5);
	diag2.addSignal('1', 15, 10);
	diag2.addSignal('0', 28, 4);
	diag2.addSignal('1', 36, 5);

	//diag2.printDiagram(std::cout);
	diag2.printSignals(std::cout);

	diag1.replace(35, diag2);
	std::cout<<"cut"<<std::endl;
	//diag1.printDiagram(std::cout);
	diag1.printSignals(std::cout);

	diag2.shift(0);
	diag2.printSignals(std::cout);


}