#include <iostream>
#include "matrixr.h"

using namespace MatrixR;

int main() {
	int rows;
	Line *mat = MatrixR::inputM(rows);
	outputM("Source Matrix:", mat, rows);
	int rows_c;
	Line *conv = filterM(mat, rows, rows_c);
	outputM("Processed Matrix:", conv, rows_c);
	sortM(conv, rows_c);
	outputM("Sorted Matrix:", conv, rows_c);
	return 0;
}
