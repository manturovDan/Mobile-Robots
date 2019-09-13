//тут надо всё переделать :((
#include <iostream>
#include "matrixr.h"

using namespace MatrixR;

int main() {
	int rows;
	int cols;
	Line *mat;
	int getm = inputM(mat, cols, rows);
	if (getm < 0) {
		std::cout<<"Input error!"<<std::endl;
		return 1;
	}

	std::cout << "Original matrix:" << std::endl;
	outputM(mat, cols, rows);
	std::cout << std::endl;

	std::cout << "Result matrix:" << std::endl;
	if (getm) {
		Line *conv;
		int filr = convertM(conv, mat, rows, cols, getm);
		if (filr == -2)
			return 1;

		outputM(conv, cols, rows - filr);
		//std::cout<<std::endl;
		//printTable(conv);
		eraseM(conv);
	}
	else {
		outputM(mat, cols, rows);
	}
	

	//std::cout<<getm<<std::endl;
	//printTable(mat);

	eraseM(mat);
	return 0;
}
