#include <iostream>
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
				//eraseM(lines, r);
				return nullptr;
			}

			std::cout << "Enter " << cols << " element(-s) for line " << (r + 1) << " in different lines" << std::endl;
			for (int c = 0; c < cols; ++c) {
				if (getNum(lines[r].row[c]) < 0) {
					//eraseM(lines, r + 1);
					return nullptr;
				}
			}
		}
		
		return lines;
	}

	void outputM(const char *msg, Line *lines, int rows) {
		std::cout << msg << std::endl;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < lines[i].elemsc; ++j)
				std::cout << lines[i].row[j] << "\t";
			std::cout << std::endl;
		}
	}

	bool evenNum(int num) {
		while (num > 0) {
			if ((num % 10) % 2 == 1) 
				return 0;
		}
		return 1;
	}

	Line *filterM(Line *source, int rows) {
		Line *conv = nullptr;

		try {
			conv = new Line[rows];
		} catch (std::bad_alloc &ba) {
			std::cout << "--------error - too many rows in matrix: " << ba.what() << std::endl;
			return nullptr;
		}

		int row_c = 0;
		int col_c = 0;

		for (int rs = 0; rs < rows; ++rs) {
			for (int cs = 0; cs < source[rs].elemsc; ++cs) {
				std::cout<<evenNum(source[rs].row[cs]);
			}
			std::cout<<std::endl;
		}
	}
}