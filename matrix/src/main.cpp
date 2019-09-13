//тут надо всё переделать :((
#include <iostream>
#include "matrixr.h"

using namespace MatrixR;

int main() {
	int rows;
	int cols;
	Line *mat;
	int getm = inputM(mat, cols, rows);
	
	std::cout << "Original matrix:" << std::endl;
	outputM(mat, cols, rows);
	std::cout << std::endl;

	Line *conv;
	int filr = convertM(conv, mat, rows, cols, getm);
	//sortM(conv, rows - filr, getm - filr);

	std::cout << "Result matrix:" << std::endl;
	outputM(conv, cols, rows - filr);

	std::cout<<std::endl;
	printTable(mat);
	std::cout<<std::endl;
	printTable(conv);

	eraseM(mat);
	eraseMA(conv);
	return 0;
}
