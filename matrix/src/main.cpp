#include <iostream>
#include "matrixr.h"

using namespace MatrixR;

int main() {
	int rows;
	Line *mat = MatrixR::inputM(rows);
	if (!mat) {
		std::cout<<"Input error!"<<std::endl;
		return 1;
	}
	
	outputM("Source Matrix:", mat, rows);
	
	int rows_c;
	Line *conv = filterM(mat, rows, rows_c);
	if(!conv)
		return 1;
	
	sortM(conv, rows_c);
	outputM("Result Matrix:", conv, rows_c);
	
	eraseM(mat, rows);
	eraseM(conv, rows_c);
	
	return 0;
}
