#include <gtest/gtest.h>

#include "diagram.h"

TEST (ConstrTest, ASCIItest) {
	char str[] = "010101001XXX000X1111";
	char str2[] = "0110XXX0010";
	timeD::Diagram diag1(str);
	timeD::Diagram diag2(str2);

	ASSERT_EQ(diag1.getLength(), 20);
	ASSERT_EQ(diag1.getSigNum(), 10);

	ASSERT_EQ(diag1.getSig(0), 0);
	ASSERT_EQ(diag1.getSigStart(0), 0);
	ASSERT_EQ(diag1.getSigLen(0), 1);

	ASSERT_EQ(diag1.getSig(1), 1);
	ASSERT_EQ(diag1.getSigStart(1), 1);
	ASSERT_EQ(diag1.getSigLen(1), 1);

	ASSERT_EQ(diag1.getSig(2), 0);
	ASSERT_EQ(diag1.getSigStart(2), 2);
	ASSERT_EQ(diag1.getSigLen(2), 1);

	ASSERT_EQ(diag1.getSig(3), 1);
	ASSERT_EQ(diag1.getSigStart(3), 3);
	ASSERT_EQ(diag1.getSigLen(3), 1);

	ASSERT_EQ(diag1.getSig(4), 0);
	ASSERT_EQ(diag1.getSigStart(4), 4);
	ASSERT_EQ(diag1.getSigLen(4), 1);

	ASSERT_EQ(diag1.getSig(5), 1);
	ASSERT_EQ(diag1.getSigStart(5), 5);
	ASSERT_EQ(diag1.getSigLen(5), 1);

	ASSERT_EQ(diag1.getSig(6), 0);
	ASSERT_EQ(diag1.getSigStart(6), 6);
	ASSERT_EQ(diag1.getSigLen(6), 2);

	ASSERT_EQ(diag1.getSig(7), 1);
	ASSERT_EQ(diag1.getSigStart(7), 8);
	ASSERT_EQ(diag1.getSigLen(7), 1);

	ASSERT_EQ(diag1.getSig(8), 0);
	ASSERT_EQ(diag1.getSigStart(8), 12);
	ASSERT_EQ(diag1.getSigLen(8), 3);

	ASSERT_EQ(diag1.getSig(9), 1);
	ASSERT_EQ(diag1.getSigStart(9), 16);
	ASSERT_EQ(diag1.getSigLen(9), 4);
	//

	ASSERT_EQ(diag2.getLength(), 11);
	ASSERT_EQ(diag2.getSigNum(), 6);

	ASSERT_EQ(diag2.getSig(0), 0);
	ASSERT_EQ(diag2.getSigStart(0), 0);
	ASSERT_EQ(diag2.getSigLen(0), 1);

	ASSERT_EQ(diag2.getSig(1), 1);
	ASSERT_EQ(diag2.getSigStart(1), 1);
	ASSERT_EQ(diag2.getSigLen(1), 2);

	ASSERT_EQ(diag2.getSig(2), 0);
	ASSERT_EQ(diag2.getSigStart(2), 3);
	ASSERT_EQ(diag2.getSigLen(2), 1);

	ASSERT_EQ(diag2.getSig(3), 0);
	ASSERT_EQ(diag2.getSigStart(3), 7);
	ASSERT_EQ(diag2.getSigLen(3), 2);

	ASSERT_EQ(diag2.getSig(4), 1);
	ASSERT_EQ(diag2.getSigStart(4), 9);
	ASSERT_EQ(diag2.getSigLen(4), 1);

	ASSERT_EQ(diag2.getSig(5), 0);
	ASSERT_EQ(diag2.getSigStart(5), 10);
	ASSERT_EQ(diag2.getSigLen(5), 1);
}

TEST (ConstrTest, commonConstr) {
	timeD::Diagram diag1('X');
	ASSERT_THROW(timeD::Diagram diag3('l'), std::invalid_argument);
	timeD::Diagram diag3('0');
	timeD::Diagram diag4('1');

	//ASSERT_EQ(diag1.getLength(), diag1.getSZlen());
	ASSERT_EQ(diag1.getSigNum(), 0);

	//ASSERT_EQ(diag3.getLength(), diag3.getSZlen());
	ASSERT_EQ(diag3.getSigNum(), 1);
	ASSERT_EQ(diag3.getSig(0), 0);

	//ASSERT_EQ(diag4.getLength(), diag4.getSZlen());
	ASSERT_EQ(diag4.getSigNum(), 1);
	ASSERT_EQ(diag4.getSig(0), 1);
}

TEST (addSig, intfTest) {
	timeD::Diagram diag1;

	ASSERT_EQ(diag1.getLength(), 0);
	ASSERT_EQ(diag1.getSigNum(), 0);

	diag1.addSignal('0', 5, 3);
	ASSERT_EQ(diag1.getLength(), 8);
	ASSERT_EQ(diag1.getSigNum(), 1);
	ASSERT_EQ(diag1.getSigStart(0), 5);
	ASSERT_EQ(diag1.getSigLen(0), 3);

	ASSERT_THROW(diag1.addSignal('X', 5, 3), std::invalid_argument);
	ASSERT_THROW(diag1.addSignal('i', 15, 3), std::invalid_argument);
	ASSERT_THROW(diag1.addSignal('X', 150, 3), std::invalid_argument);
	ASSERT_THROW(diag1.addSignal('X', 15, 300), std::invalid_argument);

	diag1.addSignal('0', 8, 4);
	ASSERT_EQ(diag1.getLength(), 12);
	ASSERT_EQ(diag1.getSigNum(), 1);

	diag1.addSignal('1', 12, 14);
	ASSERT_EQ(diag1.getLength(), 26);
	ASSERT_EQ(diag1.getSigNum(), 2);

	diag1.addSignal('1', 28, 0);
	ASSERT_EQ(diag1.getLength(), 26);
	ASSERT_EQ(diag1.getSigNum(), 2);

	ASSERT_EQ(diag1.getSig(0), 0);
	ASSERT_EQ(diag1.getSigStart(0), 5);
	ASSERT_EQ(diag1.getSigLen(0), 7);
	ASSERT_EQ(diag1.getSig(1), 1);
	ASSERT_EQ(diag1.getSigStart(1), 12);
	ASSERT_EQ(diag1.getSigLen(1), 14);
}

TEST (uniTest, intfTest) {
	timeD::Diagram diag1;
	timeD::Diagram diag2;

	diag1.addSignal('0', 5, 7);
	diag1.addSignal('1', 12, 14);

	diag2.addSignal('0', 3, 1);
	diag2.addSignal('1', 4, 8);
	diag2.addSignal('0', 12, 5);

	ASSERT_EQ(diag1.uniDiagram(diag2), 0);

	ASSERT_EQ(diag1.getLength(), 43);
	ASSERT_EQ(diag1.getSigNum(), 5);

	ASSERT_EQ(diag1.getSig(0), 0);
	ASSERT_EQ(diag1.getSigStart(0), 5);
	ASSERT_EQ(diag1.getSigLen(0), 7);
	
	ASSERT_EQ(diag1.getSig(1), 1);
	ASSERT_EQ(diag1.getSigStart(1), 12);
	ASSERT_EQ(diag1.getSigLen(1), 14);
	
	ASSERT_EQ(diag1.getSig(2), 0);
	ASSERT_EQ(diag1.getSigStart(2), 29);
	ASSERT_EQ(diag1.getSigLen(2), 1);
	
	ASSERT_EQ(diag1.getSig(3), 1);
	ASSERT_EQ(diag1.getSigStart(3), 30);
	ASSERT_EQ(diag1.getSigLen(3), 8);
	
	ASSERT_EQ(diag1.getSig(4), 0);
	ASSERT_EQ(diag1.getSigStart(4), 38);
	ASSERT_EQ(diag1.getSigLen(4), 5);

	ASSERT_EQ(diag2.uniDiagram(diag2), 0);

	ASSERT_EQ(diag2.getLength(), 34);
	ASSERT_EQ(diag2.getSigNum(), 6);

	ASSERT_EQ(diag2.getSig(0), 0);
	ASSERT_EQ(diag2.getSigStart(0), 3);
	ASSERT_EQ(diag2.getSigLen(0), 1);
	
	ASSERT_EQ(diag2.getSig(1), 1);
	ASSERT_EQ(diag2.getSigStart(1), 4);
	ASSERT_EQ(diag2.getSigLen(1), 8);
	
	ASSERT_EQ(diag2.getSig(2), 0);
	ASSERT_EQ(diag2.getSigStart(2), 12);
	ASSERT_EQ(diag2.getSigLen(2), 5);

	ASSERT_EQ(diag2.getSig(3), 0);
	ASSERT_EQ(diag2.getSigStart(3), 20);
	ASSERT_EQ(diag2.getSigLen(3), 1);
	
	ASSERT_EQ(diag2.getSig(4), 1);
	ASSERT_EQ(diag2.getSigStart(4), 21);
	ASSERT_EQ(diag2.getSigLen(4), 8);
	
	ASSERT_EQ(diag2.getSig(5), 0);
	ASSERT_EQ(diag2.getSigStart(5), 29);
	ASSERT_EQ(diag2.getSigLen(5), 5);

	ASSERT_EQ(diag2.uniDiagram(diag2), 0);

	ASSERT_EQ(diag2.getLength(), 68);
	ASSERT_EQ(diag2.getSigNum(), 12);

	ASSERT_EQ(diag2.getSig(0), 0);
	ASSERT_EQ(diag2.getSigStart(0), 3);
	ASSERT_EQ(diag2.getSigLen(0), 1);
	
	ASSERT_EQ(diag2.getSig(1), 1);
	ASSERT_EQ(diag2.getSigStart(1), 4);
	ASSERT_EQ(diag2.getSigLen(1), 8);
	
	ASSERT_EQ(diag2.getSig(2), 0);
	ASSERT_EQ(diag2.getSigStart(2), 12);
	ASSERT_EQ(diag2.getSigLen(2), 5);
	//
	ASSERT_EQ(diag2.getSig(3), 0);
	ASSERT_EQ(diag2.getSigStart(3), 20);
	ASSERT_EQ(diag2.getSigLen(3), 1);
	
	ASSERT_EQ(diag2.getSig(4), 1);
	ASSERT_EQ(diag2.getSigStart(4), 21);
	ASSERT_EQ(diag2.getSigLen(4), 8);
	
	ASSERT_EQ(diag2.getSig(5), 0);
	ASSERT_EQ(diag2.getSigStart(5), 29);
	ASSERT_EQ(diag2.getSigLen(5), 5);
	//
	ASSERT_EQ(diag2.getSig(6), 0);
	ASSERT_EQ(diag2.getSigStart(6), 37);
	ASSERT_EQ(diag2.getSigLen(6), 1);

	ASSERT_EQ(diag2.getSig(7), 1);
	ASSERT_EQ(diag2.getSigStart(7), 38);
	ASSERT_EQ(diag2.getSigLen(7), 8);
	
	ASSERT_EQ(diag2.getSig(8), 0);
	ASSERT_EQ(diag2.getSigStart(8), 46);
	ASSERT_EQ(diag2.getSigLen(8), 5);
	//
	ASSERT_EQ(diag2.getSig(9), 0);
	ASSERT_EQ(diag2.getSigStart(9), 54);
	ASSERT_EQ(diag2.getSigLen(9), 1);
	
	ASSERT_EQ(diag2.getSig(10), 1);
	ASSERT_EQ(diag2.getSigStart(10), 55);
	ASSERT_EQ(diag2.getSigLen(10), 8);
	
	ASSERT_EQ(diag2.getSig(11), 0);
	ASSERT_EQ(diag2.getSigStart(11), 63);
	ASSERT_EQ(diag2.getSigLen(11), 5);

	ASSERT_EQ(diag1.uniDiagram(diag2), 1);

	ASSERT_EQ(diag1.getLength(), 43);
	ASSERT_EQ(diag1.getSigNum(), 5);

	ASSERT_EQ(diag1.getSig(0), 0);
	ASSERT_EQ(diag1.getSigStart(0), 5);
	ASSERT_EQ(diag1.getSigLen(0), 7);

	ASSERT_EQ(diag2.uniDiagram(diag2), 1);

	ASSERT_EQ(diag2.getLength(), 68);
	ASSERT_EQ(diag2.getSigNum(), 12);

	ASSERT_EQ(diag2.getSig(0), 0);
	ASSERT_EQ(diag2.getSigStart(0), 3);
	ASSERT_EQ(diag2.getSigLen(0), 1);
}

TEST (copyTest, intfTest) {
	timeD::Diagram diag1;
	timeD::Diagram diag2;

	diag1.addSignal('0', 5, 7);
	diag1.addSignal('1', 12, 14);

	diag2.addSignal('0', 3, 1);
	diag2.addSignal('1', 4, 8);
	diag2.addSignal('0', 12, 5);

	ASSERT_EQ(diag1.copyDiagram(0), 0);
	ASSERT_EQ(diag1.getLength(), 0);
	ASSERT_EQ(diag1.getSigNum(), 0);

	ASSERT_EQ(diag2.copyDiagram(1), 0);

	for (int i = 1; i <= 1; ++i) {
		ASSERT_EQ(diag2.getLength(), 17);
		ASSERT_EQ(diag2.getSigNum(), 3);

		ASSERT_EQ(diag2.getSig(0 + 3*(i - 1)), 0);
		ASSERT_EQ(diag2.getSigStart(0 + 3*(i - 1)), 3 + 17*(i-1));
		ASSERT_EQ(diag2.getSigLen(0 + 3*(i - 1)), 1);
		
		ASSERT_EQ(diag2.getSig(1 + 3*(i - 1)), 1);
		ASSERT_EQ(diag2.getSigStart(1 + 3*(i - 1)), 4 + 17*(i-1));
		ASSERT_EQ(diag2.getSigLen(1 + 3*(i - 1)), 8);

		ASSERT_EQ(diag2.getSig(2 + 3*(i - 1)), 0);
		ASSERT_EQ(diag2.getSigStart(2 + 3*(i - 1)), 12 + 17*(i-1));
		ASSERT_EQ(diag2.getSigLen(2 + 3*(i - 1)), 5);
	}

	ASSERT_EQ(diag2.copyDiagram(5), 0);

	for (int i = 1; i <= 5; i++) {
		ASSERT_EQ(diag2.getLength(), 17*5);
		ASSERT_EQ(diag2.getSigNum(), 3*5);

		ASSERT_EQ(diag2.getSig(0 + 3*(i - 1)), 0);
		ASSERT_EQ(diag2.getSigStart(0 + 3*(i - 1)), 3 + 17*(i-1));
		ASSERT_EQ(diag2.getSigLen(0 + 3*(i - 1)), 1);
		
		ASSERT_EQ(diag2.getSig(1 + 3*(i - 1)), 1);
		ASSERT_EQ(diag2.getSigStart(1 + 3*(i - 1)), 4 + 17*(i-1));
		ASSERT_EQ(diag2.getSigLen(1 + 3*(i - 1)), 8);

		ASSERT_EQ(diag2.getSig(2 + 3*(i - 1)), 0);
		ASSERT_EQ(diag2.getSigStart(2 + 3*(i - 1)), 12 + 17*(i-1));
		ASSERT_EQ(diag2.getSigLen(2 + 3*(i - 1)), 5);
	}

	ASSERT_EQ(diag2.copyDiagram(2), 1);

	for (int i = 1; i <= 5; i++) {
		ASSERT_EQ(diag2.getLength(), 17*5);
		ASSERT_EQ(diag2.getSigNum(), 3*5);

		ASSERT_EQ(diag2.getSig(0 + 3*(i - 1)), 0);
		ASSERT_EQ(diag2.getSigStart(0 + 3*(i - 1)), 3 + 17*(i-1));
		ASSERT_EQ(diag2.getSigLen(0 + 3*(i - 1)), 1);
		
		ASSERT_EQ(diag2.getSig(1 + 3*(i - 1)), 1);
		ASSERT_EQ(diag2.getSigStart(1 + 3*(i - 1)), 4 + 17*(i-1));
		ASSERT_EQ(diag2.getSigLen(1 + 3*(i - 1)), 8);

		ASSERT_EQ(diag2.getSig(2 + 3*(i - 1)), 0);
		ASSERT_EQ(diag2.getSigStart(2 + 3*(i - 1)), 12 + 17*(i-1));
		ASSERT_EQ(diag2.getSigLen(2 + 3*(i - 1)), 5);
	}

	ASSERT_EQ(diag1.copyDiagram(2), 0);
	ASSERT_EQ(diag1.copyDiagram(0), 0);
	ASSERT_EQ(diag1.getLength(), 0);
	ASSERT_EQ(diag1.getSigNum(), 0);
}

TEST (ShiftRightTest, intfTest) {
	timeD::Diagram diag1;

	diag1.addSignal('0', 5, 7);
	diag1.addSignal('1', 12, 14);
	diag1.addSignal('0', 28, 3);
	diag1.addSignal('1', 31, 2);
	diag1.addSignal('0', 33, 7);
	diag1.addSignal('X', 42, 2);

	diag1.shift(6);

	ASSERT_EQ(diag1.getLength(), 50);
	ASSERT_EQ(diag1.getSigNum(), 5);

	ASSERT_EQ(diag1.getSig(0), 0);
	ASSERT_EQ(diag1.getSigStart(0), 11);
	ASSERT_EQ(diag1.getSigLen(0), 7);

	ASSERT_EQ(diag1.getSig(1), 1);
	ASSERT_EQ(diag1.getSigStart(1), 18);
	ASSERT_EQ(diag1.getSigLen(1), 14);

	ASSERT_EQ(diag1.getSig(2), 0);
	ASSERT_EQ(diag1.getSigStart(2), 34);
	ASSERT_EQ(diag1.getSigLen(2), 3);

	ASSERT_EQ(diag1.getSig(3), 1);
	ASSERT_EQ(diag1.getSigStart(3), 37);
	ASSERT_EQ(diag1.getSigLen(3), 2);

	ASSERT_EQ(diag1.getSig(4), 0);
	ASSERT_EQ(diag1.getSigStart(4), 39);
	ASSERT_EQ(diag1.getSigLen(4), 7);

	//
	diag1.shift(51);

	ASSERT_EQ(diag1.getLength(), 100);
	ASSERT_EQ(diag1.getSigNum(), 5);

	ASSERT_EQ(diag1.getSigStart(4), 90);
	ASSERT_EQ(diag1.getSigLen(4), 7);

	diag1.shift(3);

	ASSERT_EQ(diag1.getLength(), 100);
	ASSERT_EQ(diag1.getSigNum(), 5);

	ASSERT_EQ(diag1.getSigStart(4), 93);
	ASSERT_EQ(diag1.getSigLen(4), 7);

	diag1.shift(5);

	ASSERT_EQ(diag1.getLength(), 100);
	ASSERT_EQ(diag1.getSigNum(), 5);

	ASSERT_EQ(diag1.getSigStart(4), 98);
	ASSERT_EQ(diag1.getSigLen(4), 2);

	diag1.shift(3);

	ASSERT_EQ(diag1.getLength(), 100);
	ASSERT_EQ(diag1.getSigNum(), 4);

	ASSERT_EQ(diag1.getSigStart(3), 99);
	ASSERT_EQ(diag1.getSigLen(3), 1);

	diag1.shift(2);

	ASSERT_EQ(diag1.getLength(), 100);
	ASSERT_EQ(diag1.getSigNum(), 3);

	ASSERT_EQ(diag1.getSigStart(2), 98);
	ASSERT_EQ(diag1.getSigLen(2), 2);

	diag1.shift(300);

	ASSERT_EQ(diag1.getLength(), 100);
	ASSERT_EQ(diag1.getSigNum(), 0);
}

TEST (ShiftLeft, intfTest) {
	timeD::Diagram diag1;

	diag1.addSignal('0', 5, 7);
	diag1.addSignal('1', 12, 14);
	diag1.addSignal('0', 28, 3);
	diag1.addSignal('1', 31, 2);
	diag1.addSignal('0', 33, 7);
	diag1.addSignal('X', 42, 2);

	diag1.shift(-3);

	ASSERT_EQ(diag1.getLength(), 41);
	ASSERT_EQ(diag1.getSigNum(), 5);

	ASSERT_EQ(diag1.getSig(0), 0);
	ASSERT_EQ(diag1.getSigStart(0), 2);
	ASSERT_EQ(diag1.getSigLen(0), 7);

	diag1.shift(-4);

	ASSERT_EQ(diag1.getLength(), 37);
	ASSERT_EQ(diag1.getSigNum(), 5);

	ASSERT_EQ(diag1.getSig(0), 0);
	ASSERT_EQ(diag1.getSigStart(0), 0);
	ASSERT_EQ(diag1.getSigLen(0), 5);

	ASSERT_EQ(diag1.getSig(1), 1);
	ASSERT_EQ(diag1.getSigStart(1), 12-7);
	ASSERT_EQ(diag1.getSigLen(1), 14);

	ASSERT_EQ(diag1.getSig(2), 0);
	ASSERT_EQ(diag1.getSigStart(2), 28-7);
	ASSERT_EQ(diag1.getSigLen(2), 3);

	ASSERT_EQ(diag1.getSig(3), 1);
	ASSERT_EQ(diag1.getSigStart(3), 31-7);
	ASSERT_EQ(diag1.getSigLen(3), 2);

	ASSERT_EQ(diag1.getSig(4), 0);
	ASSERT_EQ(diag1.getSigStart(4), 33-7);
	ASSERT_EQ(diag1.getSigLen(4), 7);

	//
	diag1.shift(-6);

	ASSERT_EQ(diag1.getLength(), 31);
	ASSERT_EQ(diag1.getSigNum(), 4);

	ASSERT_EQ(diag1.getSig(0), 1);
	ASSERT_EQ(diag1.getSigStart(0), 0);
	ASSERT_EQ(diag1.getSigLen(0), 13);

	ASSERT_EQ(diag1.getSig(1), 0);
	ASSERT_EQ(diag1.getSigStart(1), 28-7-6);
	ASSERT_EQ(diag1.getSigLen(1), 3);

	ASSERT_EQ(diag1.getSig(2), 1);
	ASSERT_EQ(diag1.getSigStart(2), 31-7-6);
	ASSERT_EQ(diag1.getSigLen(2), 2);

	ASSERT_EQ(diag1.getSig(3), 0);
	ASSERT_EQ(diag1.getSigStart(3), 33-7-6);
	ASSERT_EQ(diag1.getSigLen(3), 7);

	diag1.shift(-14);

	ASSERT_EQ(diag1.getLength(), 31-14);
	ASSERT_EQ(diag1.getSigNum(), 3);

	ASSERT_EQ(diag1.getSig(0), 0);
	ASSERT_EQ(diag1.getSigStart(0), 28-7-6-14);
	ASSERT_EQ(diag1.getSigLen(0), 3);

	ASSERT_EQ(diag1.getSig(1), 1);
	ASSERT_EQ(diag1.getSigStart(1), 31-7-6-14);
	ASSERT_EQ(diag1.getSigLen(1), 2);

	ASSERT_EQ(diag1.getSig(2), 0);
	ASSERT_EQ(diag1.getSigStart(2), 33-7-6-14);
	ASSERT_EQ(diag1.getSigLen(2), 7);

	diag1.shift(-140);
	ASSERT_EQ(diag1.getLength(), 0);
	ASSERT_EQ(diag1.getSigNum(), 0);

	diag1.shift(140);

	ASSERT_EQ(diag1.getLength(), 100);
	ASSERT_EQ(diag1.getSigNum(), 0);
}

TEST (noShiftTest, intfTest) {
	timeD::Diagram diag1;
	timeD::Diagram diag2;
	diag1.addSignal('0', 5, 7);
	diag1.addSignal('1', 12, 14);

	diag2.addSignal('0', 3, 1);
	diag2.addSignal('1', 4, 8);
	diag2.addSignal('0', 12, 5);

	ASSERT_EQ(diag1.uniDiagram(diag2), 0);

	diag1.shift(0);

	ASSERT_EQ(diag1.getLength(), 43);
	ASSERT_EQ(diag1.getSigNum(), 5);

	ASSERT_EQ(diag1.getSig(0), 0);
	ASSERT_EQ(diag1.getSigStart(0), 5);
	ASSERT_EQ(diag1.getSigLen(0), 7);
	
	ASSERT_EQ(diag1.getSig(1), 1);
	ASSERT_EQ(diag1.getSigStart(1), 12);
	ASSERT_EQ(diag1.getSigLen(1), 14);
	
	ASSERT_EQ(diag1.getSig(2), 0);
	ASSERT_EQ(diag1.getSigStart(2), 29);
	ASSERT_EQ(diag1.getSigLen(2), 1);
	
	ASSERT_EQ(diag1.getSig(3), 1);
	ASSERT_EQ(diag1.getSigStart(3), 30);
	ASSERT_EQ(diag1.getSigLen(3), 8);
	
	ASSERT_EQ(diag1.getSig(4), 0);
	ASSERT_EQ(diag1.getSigStart(4), 38);
	ASSERT_EQ(diag1.getSigLen(4), 5);
}

TEST (replaceTest, intfTest) {
	timeD::Diagram diag1;
	timeD::Diagram diag2;
	timeD::Diagram diag3('0');

	diag1.addSignal('0', 5, 7);
	diag1.addSignal('1', 12, 14);

	diag2.addSignal('1', 3, 1);
	diag2.addSignal('0', 4, 7);
	diag2.addSignal('1', 11, 8);

	ASSERT_THROW(diag2.replace(20, diag1), std::invalid_argument);

	diag1.replace(14, diag2);

	ASSERT_EQ(diag1.getLength(), 19);
	ASSERT_EQ(diag1.getSigNum(), 2);

	ASSERT_EQ(diag1.getSig(0), 0);
	ASSERT_EQ(diag1.getSigStart(0), 5);
	ASSERT_EQ(diag1.getSigLen(0), 7);

	ASSERT_EQ(diag1.getSig(1), 1);
	ASSERT_EQ(diag1.getSigStart(1), 12);
	ASSERT_EQ(diag1.getSigLen(1), 7);

	diag2.replace(17, diag3);
	ASSERT_EQ(diag2.getLength(), 100);
	ASSERT_EQ(diag2.getSigNum(), 4);

	ASSERT_EQ(diag2.getSig(0), 1);
	ASSERT_EQ(diag2.getSigStart(0), 3);
	ASSERT_EQ(diag2.getSigLen(0), 1);

	ASSERT_EQ(diag2.getSig(1), 0);
	ASSERT_EQ(diag2.getSigStart(1), 4);
	ASSERT_EQ(diag2.getSigLen(1), 7);

	ASSERT_EQ(diag2.getSig(2), 1);
	ASSERT_EQ(diag2.getSigStart(2), 11);
	ASSERT_EQ(diag2.getSigLen(2), 6);

	ASSERT_EQ(diag2.getSig(3), 0);
	ASSERT_EQ(diag2.getSigStart(3), 17);
	ASSERT_EQ(diag2.getSigLen(3), 83);

	diag2.replace(4, diag1);
	ASSERT_EQ(diag2.getLength(), 19);
	ASSERT_EQ(diag2.getSigNum(), 3);

	ASSERT_EQ(diag2.getSig(0), 1);
	ASSERT_EQ(diag2.getSigStart(0), 3);
	ASSERT_EQ(diag2.getSigLen(0), 1);

	ASSERT_EQ(diag2.getSig(1), 0);
	ASSERT_EQ(diag2.getSigStart(1), 5);
	ASSERT_EQ(diag2.getSigLen(1), 7);

	ASSERT_EQ(diag2.getSig(2), 1);
	ASSERT_EQ(diag2.getSigStart(2), 12);
	ASSERT_EQ(diag2.getSigLen(2), 7);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}