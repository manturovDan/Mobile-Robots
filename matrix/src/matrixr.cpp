#include <iostream>
#include "matrixr.h"

namespace MatrixR {
	int getNum(int &inp) {
		std::cin >> inp;
		if (!std::cin.good())
			return -1;
		if(std::abs(inp) > 100000000)
			return 2;
		return 1;
	}

	int getNatNum(const char *welcome, const char *again, int &inp) {
		bool moretime = false;
		int gnStatus;
		do {
			if (moretime)
				std::cout << again << std::endl;
			else
				std::cout << welcome << std::endl;
			gnStatus = getNum(inp);
			if (gnStatus < 0)
				return -1;
			if (gnStatus == 2)
				inp = -1;

			moretime = true;
		} while (inp < 1);
		
		return 0;
	}

	int inputM(Line *&origin, int &cols, int &rows) {
		const char *repeat = "Input natural number in the correct range!";

		if (getNatNum("Enter count of rows:", repeat, rows) < 0 || getNatNum("Enter count of columns:", repeat, cols) < 0)
			return 1;


		int gnStatus;
		int inpNum;
		origin = nullptr;
		Line *curPtr = nullptr;
		Line *newPtr = nullptr;

		nzel *lastone = nullptr;
		nzel *current = nullptr;

		for(int rw = 0; rw < rows; ++rw) {
			std::cout << "Input number(-s) of " << (rw + 1) << " row by Enter:"<<std::endl;
			for (int col = 0; col < cols; ++col) {
				do {
					gnStatus = getNum(inpNum);
					if (gnStatus == -1) {
						//erase
						return 1;
					}
				} while (gnStatus != 1);

				if (inpNum) {
					current = new nzel;
					current->number =  inpNum;
					current->position = col;
					current->next =  nullptr;

					if(lastone) 
						lastone->next = current;
					else {
						if (!curPtr) {
							origin = new Line;
							curPtr = origin;
						}
						else {
							curPtr->nextRow = new Line;
							curPtr = curPtr->nextRow;
						}
						curPtr->elemsc = cols;
						curPtr->nzelems = 0;
						curPtr->number = rw;
						curPtr->row = current;
						curPtr->nextRow = nullptr;
					}
					
					lastone = current;

				}

			}
			
			lastone = nullptr;
		}

		return 0;
	}

	void printTable(Line *line) {
		while (line != nullptr) {
			std::cout << line->number << " row:";
			nzel *pnt = line->row;
			while(pnt != nullptr) {
				std::cout << " -> {" << pnt->number << ", " << pnt->position << "}";
				pnt = pnt->next;
			}
			std::cout << std::endl;
			line = line->nextRow;
		}
	}

	void outputM(Line *line, int cols, int rows) {
		for (int rw = 0; rw < rows; ++rw) {
			if (line->number == rw) {
				nzel *lel = line->row;
				for (int c = 0; c < cols; ++c) {
					if (lel->position == c) {
						std::cout << lel->number << " ";
						if (lel->next)
							lel = lel->next;
					}
					else
						std::cout << "0 ";
				}
				if (line->nextRow)
					line = line->nextRow;
			}
			else {
				for (int c = 0; c < cols; ++c)
					std::cout << "0 ";
			}
			std::cout << std::endl;
		}
	}
}