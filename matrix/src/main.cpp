#include <iostream>
#include "matrixr.h"

using namespace MatrixR;

int main() {
	int rows;
	Line *mat = MatrixR::inputM(rows);
	outputM("Source Matrix:", mat, rows);
	int rows_c;
	Line *conv = filterM(mat, rows, rows_c);
	outputM("Result Matrix:", conv, rows_c);
	return 0;
}
