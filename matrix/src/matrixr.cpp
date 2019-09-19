#include <iostream>
#include <cstring>
#include <cstdlib>
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
			else if (strcmp(welcome,"") != 0)
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

	int inpInSegment(const char *again, int &inp, int start, int end) {
		bool more = false;
		int gnStatus;
		while (1) {
			if (more)
				std::cout << again << std::endl;
			gnStatus = getNum(inp);
			if (gnStatus < 0)
				return -1;
			if (gnStatus == 2)
				more = true;
			else if (inp >= start && inp <= end)
				return 0;
			else
				more = true;
		}
	}

	int choise() {
		const char *repeat = "Input correct number!";

		int chs;
		while (1) {
			if (getNatNum("Enter 1 to input matrix fully OR input 2 to input onle non-zero elements:", repeat, chs))
				return -2;
			else if (chs > 2) {
				std::cout<<repeat<<std::endl;
				continue;
			}
			else 
				return chs;
		}
	}

	int inputNZ(Line *&origin, int &cols, int &rows) {
		const char *repeat = "Input number in the correct range!";

		if (getNatNum("Enter count of rows:", repeat, rows) < 0 || getNatNum("Enter count of columns:", repeat, cols) < 0)
			return -2; //input error


		int gnStatus;
		int nzcount;
		int crStatus;
		int inpNum;

		int curRow = -1;
		int nzCount;

		origin = nullptr;
		Line *curPtr = nullptr;
		nzel *lastone = nullptr;

		std::cout << "Input count of row(-s) with non-zero elements from 0 to " << rows << ":" << std::endl;
		if (inpInSegment(repeat, nzcount, 0, rows) < 0)
			return -2;

		for (int i = 0; i < nzcount; ++i) {
			if(curRow + 2 > rows) {
				nzCount = i;
				std::cout << "Reduction of rows count" << std::endl;
				break;
			}

			int oldRow = curRow;

			std::cout << "Input number of new row with non-zero elements from " << (curRow + 2) << " to " << rows << ", " << (nzcount - i)  << " left:" << std::endl;
			if (inpInSegment(repeat, curRow, curRow + 2, rows) < 0) {
				eraseM(origin);
				return -2;
			}

			--curRow;

			std::cout<< "Input count of non-zero numbers in " << (curRow + 1) << " row from 1 to " << cols << ":" <<std::endl;
			if (inpInSegment(repeat, nzCount, 1, cols) < 0) {
				eraseM(origin);
				return -2;
			}

			
			int position = -1;
			for (int el = 0; el < nzCount; ++el) {
				if (position + 2 > cols) {
					nzCount = el;
					std::cout << "Reduction of elements count" << std::endl;
					break;
				}

				int oldPos = position;
				std::cout << "Input position of " << (el+1) << "/" << nzCount << " element in " << (curRow + 1) << " row from " << (oldPos + 2) << " to " << cols << ":" << std::endl;
				if (inpInSegment(repeat, position, (oldPos + 2), cols) < 0) {
					eraseM(origin);
					return -2;
				}

				--position;

				std::cout << "Input number:" << std::endl;
			
				inpNum = 0;
				while (1) {
					if (inpInSegment(repeat, inpNum, -100000000, 100000000) < 0) //non-zero {
						eraseM(origin);
						return -2;
					}
					if(inpNum != 0)
						break;
					std::cout << "Input non-zero value" << std::endl;
				}

				if(inpNum) {
					std::cout<<"Correct. Row"<<curRow<<" Col:" << position <<" El:" << inpNum << std::endl;
					crStatus = createPoint(origin, curPtr, lastone, position, curRow, cols, inpNum);
					if (crStatus < 0) {
						eraseM(origin);
						return -2;
					}
				}
				
			}

			lastone = nullptr;

		}

		return nzcount;
	}

	int inputM(Line *&origin, int &cols, int &rows) {
		const char *repeat = "Input number in the correct range!";

		if (getNatNum("Enter count of rows:", repeat, rows) < 0 || getNatNum("Enter count of columns:", repeat, cols) < 0)
			return -2; //input error


		int gnStatus;
		int inpNum;
		origin = nullptr;
		Line *curPtr = nullptr;
		nzel *lastone = nullptr;
		nzel *current = nullptr;

		int nzcount = 0;

		for(int rw = 0; rw < rows; ++rw) {
			std::cout << "Input number(-s) of " << (rw + 1) << " row by Enter:" << std::endl;
			for (int col = 0; col < cols; ++col) {
				do {
					gnStatus = getNum(inpNum);
					if (gnStatus == -1) {
						return -2;
					}
				} while (gnStatus != 1);

				if (inpNum) {
					current = nullptr;
					try {
						current = new nzel;
					} catch (std::bad_alloc &ba) {
						std::cout << "Memory allocation error!" << ba.what() << std::endl;
						eraseM(origin);
						return -1; //memory error
					}

					current->number =  inpNum;
					current->position = col;
					current->next =  nullptr;

					if(lastone) 
						lastone->next = current;
					else {
						if (!curPtr) {
							origin = nullptr;
							try {
								origin = new Line;
							} catch (std::bad_alloc &ba) {
								std::cout << "Memory allocation error!" << ba.what() << std::endl;
								eraseM(origin);
								return -1; //memory error
							}
							curPtr = origin;
						}
						else {
							try {
								curPtr->nextRow = new Line;
							} catch (std::bad_alloc &ba) {
								std::cout << "Memory allocation error!" << ba.what() << std::endl;
								eraseM(origin);
								return -1; //memory error
							}

							curPtr = curPtr->nextRow;
						}

						++nzcount;
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

		return nzcount;
	}

	int createPoint(Line *&origin, Line *&curPtr, nzel *&lastone, int col, int row, int cols, int inpNum) {
		nzel *current = nullptr;

		int ret = 0;
		
		try {
			current = new nzel;
		} catch (std::bad_alloc &ba) {
			std::cout << "Memory allocation error!" << ba.what() << std::endl;
			return -1; //memory error
		}

		current->number =  inpNum;
		current->position = col;
		current->next =  nullptr;

		if(lastone) 
			lastone->next = current;
		else {
			if (!curPtr) {
				origin = nullptr;
				try {
					origin = new Line;
				} catch (std::bad_alloc &ba) {
					std::cout << "Memory allocation error!" << ba.what() << std::endl;
					return -1; //memory error
				}
				curPtr = origin;
			}
			else {
				try {
					curPtr->nextRow = new Line;
				} catch (std::bad_alloc &ba) {
					std::cout << "Memory allocation error!" << ba.what() << std::endl;
					return -1; //memory error
				}

				curPtr = curPtr->nextRow;
			}

			curPtr->elemsc = cols;
			curPtr->nzelems = 0;
			curPtr->number = row;
			curPtr->row = current;
			curPtr->nextRow = nullptr;
			ret = 1;
		}

		lastone = current;

		return ret;
	}

	void printTable(Line *line) {
		while (line != nullptr) {
			std::cout << line->number << " row all:" << line->elemsc << " nz: " << line->nzelems;
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
		if (line) {
			for (int rw = 0; rw < rows; ++rw) {
				if (line->number == rw) {
					if (line->row) {
						nzel *lel = line->row;
						for (int c = 0; c < line->elemsc; ++c) {
							if (lel->position == c) {
								std::cout << lel->number << " ";
								if (lel->next)
									lel = lel->next;
							}
							else
								std::cout << "0 ";
						}

						std::cout << std::endl;
					}
					else if (line->elemsc) {
						for (int c = 0; c < line->elemsc; ++c)
							std::cout << "0 ";
						std::cout << std::endl;
					}

					if (line->nextRow)
						line = line->nextRow;
				}
				else {
					for (int c = 0; c < cols; ++c)
						std::cout << "0 ";
					std::cout << std::endl;
				}
			}
		}
		else {
			for (int rw = 0; rw < rows; ++rw) {
				for (int c = 0; c < cols; ++c) 
					std::cout << "0 ";
				std::cout << std::endl;
			}
		}
	}

	bool evenDNum(int num) {
		num = std::abs(num);
		while (num > 0) {
			if ((num % 10) % 2 == 1) 
				return 0;
			num /= 10;
		}
		return 1;
	}

	int convertM(Line *&conv, Line *line, int rows, int cols, int nzcou,  bool (*crit)(int)) {
		if (line) {
			conv = new Line[nzcou];
			int crow = 0;
			int empsp = 0;
			while (line != nullptr) {
				nzel *rel = line->row;
				nzel *current = nullptr;
				conv[crow].row = nullptr;
				conv[crow].elemsc = cols;
				conv[crow].nzelems = 0;
				conv[crow].number = line->number - empsp;

				while(rel != nullptr) {
					if (crit(rel->number)) {
						if (conv[crow].row) {
							try {
								current->next = new nzel;
							} catch (std::bad_alloc &ba) {
								std::cout << "Memory allocation error!" << ba.what() << std::endl;
								eraseM(line);
								eraseMA(conv);
								return -2; //memory error
							}
							current = current->next;
						}
						else {
							try {
								conv[crow].row = new nzel;
							} catch (std::bad_alloc &ba) {
								std::cout << "Memory allocation error!" << ba.what() << std::endl;
								eraseM(line);
								eraseMA(conv);
								return -2; //memory error
							}
							current = conv[crow].row;
						}

						current->number = rel->number;
						current->position = rel->position - (line->elemsc - conv[crow].elemsc);
						//std::cout<<current->number<<std::endl;
						++conv[crow].nzelems;
					}
					else {
						--conv[crow].elemsc;
					}

					rel = rel->next;
				}

				line = line->nextRow;
				if (!conv[crow].elemsc) {
					++empsp;
					continue;
				}

				//if (crow < nzcou - empsp - 1)
				//	conv[crow].nextRow = &(conv[crow+1]);

				++crow;

			}

			sortM(conv, rows - empsp, nzcou - empsp);

			Line *rnewl = nullptr;
			Line *cur = nullptr;
			for (int i = 0; i < nzcou - empsp; ++i) {
				if (!i) {
					try {
						rnewl = new Line { conv[i].elemsc, conv[i].nzelems, conv[i].number, conv[i].row, nullptr };
					} catch (std::bad_alloc &ba) {
						std::cout << "Memory allocation error!" << ba.what() << std::endl;
						eraseM(line);
						eraseMA(conv);
						return -2; //memory error
					}
					cur = rnewl;
				}
				else {
					try {
						cur->nextRow = new Line { conv[i].elemsc, conv[i].nzelems, conv[i].number, conv[i].row, nullptr };
					} catch (std::bad_alloc &ba) {
						std::cout << "Memory allocation error!" << ba.what() << std::endl;
						eraseM(line);
						eraseM(rnewl);
						eraseMA(conv);
						return -2; //memory error
					}
					cur = cur->nextRow;
				}
			}
			delete[] conv;
			conv = rnewl;
			
			return empsp;
		}
		else {
			conv = nullptr;
			return -1; //zero matrix
		}

	}

	void sortM(Line *&matr, int rows, int nzr) {
		std::qsort(matr, nzr, sizeof(Line), complines);

		for (int i = 0; i < nzr; ++i) {
			matr[i].number = i + rows - nzr;
			if (i < nzr - 1) 
				matr[i].nextRow = &(matr[i+1]);
			else
				matr[i].nextRow = nullptr;
		}
	}

	int complines(const void *line1, const void *line2) {
		if ((*(Line*)line1).nzelems > (*(Line*)line2).nzelems)
			return 1;
		return -1;
	}

	void delnm(nzel *curel) {
		while (curel) {
			nzel *nextel = curel->next;
			delete curel;
			curel = nextel;
		}
	}

	void eraseM(Line *matr) {
		while (matr) {
			delnm(matr->row);
			Line *tmat = matr->nextRow;
			delete matr;
			matr = tmat;
		}
	}

	void eraseMA(Line *mat) {
		Line *matr = mat;
		while (matr) {
			delnm(matr->row);
			matr = matr->nextRow;
		}

		delete[] mat;
	}
}