#include <iostream>
#include "matrixr.h"

using namespace MatrixR;

int main() {
	int rows;
	Line *mat = MatrixR::inputM(rows);
	outputM("Source Matrix:", mat, rows);
	filterM(mat, rows);
	return 0;
}
