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
	6. Print diagram\n\
	0. Exit" << std:: endl;	
		
		inpSmt(choise);
		if(choise >= 0 && choise <= 6)
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
		else if (act == 2) {
			int diagLeft = chooseDiag(2, "Choose the root diagram");
			int diagRight = chooseDiag(2, "Choose diagram which to add");

			timeD::Diagram *root;
			timeD::Diagram *add;
			if (diagLeft == 1)
				root = &diag1;
			else
				root = &diag2;

			if (diagRight == 1)
				add = &diag1;
			else
				add = &diag2;

			if(root->uniDiagram(*add)) {
				std::cout << "Unsuccessfull union" << std::endl;
				return 1;
			}

			std::cout << "Successfull union" << std::endl;
			return 0;

		}
		else if (act == 3) {
			int diagLeft = chooseDiag(2, "Choose the root diagram");
			int diagRight = chooseDiag(2, "Choose diagram which to add");

			timeD::Diagram *root;
			timeD::Diagram *add;
			if (diagLeft == 1)
				root = &diag1;
			else
				root = &diag2;

			if (diagRight == 1)
				add = &diag1;
			else
				add = &diag2;

			std::cout << "Input moment of time from which root diagram will be changed" << std::endl;
			int moment;
			inpSmt(moment);

			try {
				root->replace(moment, *add);
			} catch (std::exception &ex) {
				std::cout << ex.what() << std::endl;
				return 1;
			}

			std::cout << "Successfull replacing" << std::endl;
			return 0;
		}
		else if (act == 4) {
			int diag = chooseDiag(2, "Choose diagram to copy");
			
			timeD::Diagram *work;
			if (diag == 1)
				work = &diag1;
			else
				work = &diag2;

			std::cout << "Input count of copies" << std::endl;
			int ccnt;
			inpSmt(ccnt);

			if(work->copyDiagram(ccnt)) {
				std::cout << "Error. Diagram will be too big" << std::endl;
				return 1;
			}

			std::cout << "Successfull copying" << std::endl;
			return 0;
		}
		else if (act == 5) {
			int diag = chooseDiag(2, "Choose diagram to shift");
			
			timeD::Diagram *work;
			if (diag == 1)
				work = &diag1;
			else
				work = &diag2;

			std::cout << "Input number of shift (+/-)" << std::endl;
			int shf;
			inpSmt(shf);

			if(work->shift(shf)) {
				std::cout << "Error while shifting" << std::endl;
				return 1;
			}

			std::cout << "Successfull shifting" << std::endl;
			return 0;
		}
		else if (act == 6) {
			int diag = chooseDiag(2, "Choose diagram to print");

			timeD::Diagram *work;
			if (diag == 1)
				work = &diag1;
			else
				work = &diag2;

			work->printDiagram(std::cout);
			work->printSignals(std::cout);

			return 0;
		}

		return -1;
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