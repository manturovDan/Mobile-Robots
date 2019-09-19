#include <iostream>
#include "matrixr.h"

using namespace MatrixR;

int main() {
	int rows;
	int cols;
	Line *mat;
	int chs = choise();
	if(chs < 1) {
		std::cout<<"Input error!"<<std::endl;
		return 1;
	}

	int getm;
	if (chs == 1) {
		getm = inputM(mat, cols, rows);
	}
	else {
		getm = inputNZ(mat, cols, rows);
	}
	
	if (getm < 0) {
		std::cout<<"Error!"<<std::endl;
		return 1;
	}

	std::cout << "Original matrix:" << std::endl;
	outputM(mat, cols, rows);
	std::cout << std::endl;

	std::cout << "Result matrix:" << std::endl;
	
	Line *conv;
	int filr = convertM(conv, mat, rows, cols, getm, evenDNum);
	if (filr == -2)
		return 1;
	else if (filr == -1) {
		filr = 0;
	}


	outputM(conv, cols, rows - filr);
	//std::cout<<std::endl;
	//printTable(conv);
	eraseM(conv);
	
	

	//std::cout<<getm<<std::endl;
	std::cout<<"\nReference List"<<std::endl;
	printTable(mat);

	eraseM(mat);
	return 0;
}
