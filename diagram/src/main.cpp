#include <iostream>

#include "diagram.h"

int main() {
	std::cout<<"Hello"<<std::endl;
	timeD::Diagram diag1;
	std::cout << diag1.getLength() <<std::endl;
	diag1.addSignal('1', 5, 3);
	diag1.addSignal('0', 8, 4);
	diag1.addSignal('X', 12, 88);
	std::cout << diag1.getLength() <<std::endl;
	diag1.printDiagram(std::cout);
	diag1.printSignals(std::cout);
}