#include <iostream>
#include <cstring>
#include <cstdlib>
#include "matrixr.h"

namespace MatrixR {
	int getNum(int &inp) {
		std::cin >> inp;
		if (!std::cin.good())
			return -1;
		return 1;
	}

	int getNatNum(const char *welcome, const char *again, int &inp) {
		bool moretime = false;
		do {
			if (moretime)
				std::cout << again << std::endl;
			else
				std::cout << welcome << std::endl;
			if (getNum(inp) < 0)
				return -1;

			moretime = true;
		} while (inp < 1);
		
		return 0;
	}

	Line *inputM(int &rows) {
		int cols;

		const char *repeat = "You are wrong. Try again!";

		if (getNatNum("Enter count of rows:", repeat, rows) < 0 || getNatNum("Enter count of columns:", repeat, cols) < 0)
			return nullptr;

		Line *lines = nullptr;

		try {
			lines = new Line[rows];
		} catch (std::bad_alloc &ba) {
			std::cout << "--------error - too many rows in matrix: " << ba.what() << std::endl;
			return nullptr;
		}

		for (int r = 0; r < rows; ++r) {
			lines[r].elemsc = cols;

			try {
				lines[r].row = new int[cols];
			} catch (std::bad_alloc &ba) {
				std::cout << "--------error - too many rows in matrix: " << ba.what() << std::endl;
				eraseM(lines, r);
				return nullptr;
			}

			std::cout << "Enter " << cols << " element(-s) for line " << (r + 1) << " in different lines" << std::endl;
			for (int c = 0; c < cols; ++c) {
				if (getNum(lines[r].row[c]) < 0) {
					eraseM(lines, r + 1);
					return nullptr;
				}
			}
		}
		
		return lines;
	}

	void outputM(const char *msg, Line *lines, int rows) {
		std::cout << msg << std::endl;
		for (int i = 0; i < rows; ++i) {
			//std::cout << "(" << lines[i].elemsc << ") ["  << lines[i].nzelems << "]\t";
			for (int j = 0; j < lines[i].elemsc; ++j)
				std::cout << lines[i].row[j] << "\t";
			std::cout << std::endl;
		}
	}

	bool evenDNum(int num) {
		while (num > 0) {
			if ((num % 10) % 2 == 1) 
				return 0;
			num /= 10;
		}
		return 1;
	}

	int compLines(const void *line1, const void *line2) {
		if ((*(Line*)line1).nzelems > (*(Line*)line2).nzelems)
			return 1;
		return -1;
	}

	Line *filterM(Line *source, int rows, int &row_c) {
		Line *conv = nullptr;

		try {
			conv = new Line[rows];
		} catch (std::bad_alloc &ba) {
			std::cout << "--------error - too many rows in matrix: " << ba.what() << std::endl;
			eraseM(source, rows);
			return nullptr;
		}

		row_c = -1;
		int col_c;

		bool fitrow;

		for (int rs = 0; rs < rows; ++rs) {
			fitrow = 0;
			col_c = 0;

			for (int cs = 0; cs < source[rs].elemsc; ++cs) {
				if(evenDNum(source[rs].row[cs])) {
					if (fitrow == 0) {
						fitrow = 1;
						++row_c;		
						conv[row_c].nzelems = 0;
						conv[row_c].elemsc = 0;
						
						try {
							conv[row_c].row = new int[source[rs].elemsc];
						} catch (std::bad_alloc &ba) {
							std::cout << "--------error - too many rows in matrix: " << ba.what() << std::endl;
							eraseM(source, rows);
							eraseM(conv, row_c+1);
							return nullptr;
						}

					}
					//std::cout << source[rs].row[cs] << " ";
					conv[row_c].row[col_c] = source[rs].row[cs];

					if (conv[row_c].row[col_c] != 0) 
						conv[row_c].nzelems++;

					conv[row_c].elemsc++;
					++col_c;
				}
			}

			//std::cout << std::endl;
		}

		++row_c;

		for (int rnc = 0; rnc < row_c; ++rnc) {
			int *new_line;
			
			try {
				new_line = new int[conv[rnc].elemsc];
			} catch (std::bad_alloc &ba) {
				std::cout << "--------error - too many rows in matrix: " << ba.what() << std::endl;
				eraseM(source, rows);
				eraseM(conv, row_c);
				return nullptr;
			}

			std::memcpy(new_line, conv[rnc].row, sizeof(int) * conv[rnc].elemsc);
			delete[] conv[rnc].row;
			conv[rnc].row = new_line;
		}

		return conv;
	}

	void sortM(Line *matr, int rows) {
		std::qsort(matr, rows, sizeof(Line), compLines);
	}

	void eraseM(Line *&lines, int rows) {
		for (int i = 0; i < rows; ++i)
			delete[] lines[i].row;
		delete[] lines;
	}
}