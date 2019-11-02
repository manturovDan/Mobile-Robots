#include <iostream>
#include "diagram.h"
#include "diagfile.h"

template <class T>
int inpSmt(T &inp, bool unneg = false, const char *again = "Input error! Try again!") {
    bool more = false;
    while (1) {
        if (more)
            std::cout << again << std::endl;

        std::cin >> inp;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            more = 1;
            continue;
        }
        if(std::abs(inp) > 100000000 || (unneg && inp < 0))
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
	7. Make one diagram as the segment of another one\n\
	8. Create diagram from ASCII\n\
	9. Read diagram from .txt file\n\
	10. Write to .txt file\n\
	0. Exit" << std:: endl;

        inpSmt(choise);
        if(choise >= 0 && choise <= 10)
            return choise;

        std::cout << "Incorrect value!" << std::endl;
    }
}

int chooseDiag(int diags, const char *welcome) {
    int choise;
    std::cout << welcome << std::endl;

    while (1) {
        std::cout << "Choose one of " << diags << " diagrams" << std::endl;
        inpSmt(choise);
        if(choise > 0 && choise <= diags)
            return choise;

        std::cout << "Incorrect value!" << std::endl;
    }
}

timeD::Diagram * getFileAndDiag(char* welcome, timeD::Diagram & diag1, timeD::Diagram & diag2, std::string &filename) {
    int dgr = chooseDiag(2, welcome);
    timeD::Diagram *diag;

    if (dgr == 1)
        diag = &diag1;
    else
        diag = &diag2;

    std::cout << "Input path to file" << std::endl;
    fileD::inpString(filename);
    return diag;

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

        std::cout << "Correct adding" << std::endl;
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

        try {
            (*root) += (*add);
        }
        catch (std::exception &ex) {
            std::cout << ex.what() << std::endl;
            std::cout << "Incorrect union" << std::endl;
            return 1;
        }

        std::cout << "Correct union" << std::endl;
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

        std::cout << "Correct replacing" << std::endl;
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

        std::cout << "Correct copying" << std::endl;
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

        if (shf >= 0)
            (*work)>>shf;
        else
            (*work)<<(-shf);


        std::cout << "Correct shifting" << std::endl;
        return 0;
    }
    else if (act == 6) {
        int diag = chooseDiag(2, "Choose diagram to print");

        timeD::Diagram *work;
        if (diag == 1)
            work = &diag1;
        else
            work = &diag2;

        std::cout << (*work) << std::endl;

        return 0;
    }
    else if (act == 7) {
        int d1 = chooseDiag(2, "Choose source diagram");
        int d2 = chooseDiag(2, "Choose victim diagram (well be cleared)");
        int a;
        int b;

        timeD::Diagram *from;
        timeD::Diagram *to;

        if (d1 == 1)
            from = &diag1;
        else
            from = &diag2;

        if (d2 == 1)
            to = &diag1;
        else
            to = &diag2;

        std::cout << "Input left boundary number - segment [ )" << std::endl;
        inpSmt(a, true);
        std::cout << "Input right boundary number" << std::endl;
        inpSmt(b, true);

        try {
            (*from)(a, b, *to);
        } catch (std::exception &ex) {
            std::cout << ex.what() << std::endl;
            return 1;
        }

        std::cout << "Correct segment copying" << std::endl;

        return 0;
    }
    else if (act == 8) {
        int dgr = chooseDiag(2, "Choose diagram to input");

        timeD::Diagram *diag;

        if (dgr == 1)
            diag = &diag1;
        else
            diag = &diag2;

        std::cout << "Input ASCII string of symbols" << std::endl;

        std::cin.get();
        std::cin >> (*diag);

        if (!std::cin.good()) {
            std::cout << "Invalid input (stream error)" <<std::endl;
            std::cin.clear();
            return 1;
        }

        std::cout << "Correctly created" << std::endl;

        return 0;
    }
    else if (act == 9) {
        std::string filename;
        char welcome[] = "Choose diagram to input";
        timeD::Diagram *diag = getFileAndDiag(welcome, diag1, diag2, filename);

        return fileD::readTextDiag(filename, *diag);
    }
    else if (act == 10) {
        std::string filename;
        char welcome[] = "Choose diagram to input";
        timeD::Diagram *diag = getFileAndDiag(welcome, diag1, diag2, filename);

        return fileD::writeTextDiag(filename, *diag);
    }

    return -1;
}

int main() {
    timeD::Diagram diag1;
    timeD::Diagram diag2;

    std::cout << "Bonus - new branch Realisation\nTwo diagrams were created (Empty)." << std::endl;

    int choise;
    while (1) {
        choise = chooseAct();
        if (!choise)
            return 0;
        launchFunc(diag1, diag2, choise);

    }


}