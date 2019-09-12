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

	int filr = convertM(conv, mat, rows, cols, getm);
	printTable(conv);
	outputM(conv, cols, rows - filr);

	sortM(conv, rows - filr, getm - filr);
	printTable(conv);
	outputM(conv, cols, rows - filr);

	return 0;
}
