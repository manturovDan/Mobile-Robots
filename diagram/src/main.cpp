#include <iostream>
#include "diagram.h"

template <class T>
int inpSmt(T &inp, bool unneg = false, const char *again = "Input error! Try again!") {
	bool more = false;
	int gnStatus;
	while (1) {
		if (more) 
			std::cout << again << std::endl;

		std::cin >> inp;
		if (!std::cin.good())
			throw std::invalid_argument("Invalid input");
		if(std::abs(inp) > 100000000 || unneg && inp < 0)
			more = true;
		else 
			return 0;
	}
}

int chooseAct() {
	int choise;
	while (1) {
		std::cout<<"Choose the number:\n\
	1. Input signal segment\n\
	2. Unite two diagrams\n\
	3. Replace the first diagram on the second (from definetely time)\n\
	4. Copy the diagram n times\n\
	5. Shift the diagram\n\
	0. Exit" << std:: endl;	
		
		inpSmt(choise);
		if(choise >= 0 && choise <= 5)
			return choise;

		std::cout << "Incorrect value!" << std::endl;
	}
}

int chooseDiag(int diags, const char *welcome) {
	int choise;
	std::cout << welcome << std::endl;
	
	while (1) {
		std::cout << "Choose one of " << diags << " diagrams or 0 to go back" << std::endl;
		inpSmt(choise);
		if(choise >= 0 && choise <= diags)
			return choise;

		std::cout << "Incorrect value!" << std::endl;
	}
}

int launchFunc(timeD::Diagram &diag1, timeD::Diagram &diag2, int act) {
	if (act == 1) {
			int diag = chooseDiag(2, "Choose diagram to adding segment");

			std::cout << "Input signal (0 or 1 or X)" << std::endl;
			char symb;
			inpSmt(symb);

			if (symb != '0' && symb != '1' && symb != 'X') {
				std::cout << "Incorrect signal" << std::endl;
				return 1;
			}

			int maxStart;
			int maxLen;
			timeD::Diagram *work;

			if (diag == 1)
				work = &diag1;
			else
				work = &diag2;
			
			int start;
			int len;

			std::cout << "Input start time ot the segment" << std::endl;
			inpSmt(start);
			std::cout << "Input length of the segment" << std::endl;
			inpSmt(len);

			try {
				work->addSignal(symb, start, len);
			} catch (std::exception &ex) {
				std::cout << ex.what() << std::endl;
				return 1;
			}

			std::cout << "Successful adding" << std::endl;
			return 0;
		}
		else {

		}
}

int main() {
	timeD::Diagram diag1;
	timeD::Diagram diag2;
	
	std::cout << "Two diagrams have created (Empty)." << std::endl;

	int choise;
	while (1) {
		choise = chooseAct();
		if (!choise)
			return 0;
		launchFunc(diag1, diag2, choise);

	}

}