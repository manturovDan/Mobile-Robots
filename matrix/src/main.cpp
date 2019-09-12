//тут надо всё переделать :((
#include <iostream>
#include "matrixr.h"

using namespace MatrixR;

int main() {
	int rows;
	int cols;
	Line *mat;
	int getm = inputM(mat, cols, rows);
	
	printTable(mat);
	outputM(mat, cols, rows);

	Line *conv;

	convertM(conv, mat, rows, cols, getm);
	printTable(conv);
	outputM(conv, cols, rows);

	return 0;
}
