//тут надо всё переделать :((
#include <iostream>
#include "matrixr.h"

using namespace MatrixR;

int main() {
	int rows;
	Line *mat = MatrixR::inputM(rows);
	
	printTable(mat);
	return 0;
}
