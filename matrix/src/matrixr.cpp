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

	Line *inputM(int &rows) {
		int cols;
		const char *repeat = "Input natural number in the correct range!";

		if (getNatNum("Enter count of rows:", repeat, rows) < 0 || getNatNum("Enter count of columns:", repeat, cols) < 0)
			return nullptr;

		std::cout<<rows<<" "<<cols<<std::endl;

		int gnStatus;
		int inpNum;
		Line *origin = nullptr;
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
						return nullptr;
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

		return origin;
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
}