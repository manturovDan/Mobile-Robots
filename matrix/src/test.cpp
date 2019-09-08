#include <gtest/gtest.h>
#include "matrixr.h"

using namespace MatrixR;

TEST (PreTest, natDNum) {
	ASSERT_EQ(0, evenDNum(12));
	ASSERT_EQ(1, evenDNum(22));
	ASSERT_EQ(1, evenDNum(0));
	ASSERT_EQ(0, evenDNum(12222));
	ASSERT_EQ(1, evenDNum(4440));
	ASSERT_EQ(0, evenDNum(6554));
	ASSERT_EQ(1, evenDNum(6080606));
	ASSERT_EQ(1, evenDNum(2000088));
	ASSERT_EQ(0, evenDNum(121111));
	ASSERT_EQ(1, evenDNum(404));
	ASSERT_EQ(0, evenDNum(1));
	ASSERT_EQ(0, evenDNum(7794955));
	ASSERT_EQ(0, evenDNum(210888));
	ASSERT_EQ(1, evenDNum(42604));
	ASSERT_EQ(0, evenDNum(1000000));
}

TEST (matrTest, mat1) {
	int *row1 = new int[3] {4, 0, 66};
	int *row2 = new int[3] {1, 2, 3};

	Line *lines = new Line[2] {{3, 0, row1}, {3, 0, row2}};
	outputM("Test", lines, 2);
	
	int rows_c;
	Line *conv = filterM(lines, 2, rows_c);
	outputM("TestC", conv, 2);

	ASSERT_EQ(2, rows_c);
	ASSERT_EQ(3, conv[0].elemsc);
	ASSERT_EQ(1, conv[1].elemsc);
	ASSERT_EQ(2, conv[0].nzelems);
	ASSERT_EQ(1, conv[1].nzelems);

	sortM(conv, rows_c);
	outputM("TestS", conv, 2);
	ASSERT_EQ(2, rows_c);
	ASSERT_EQ(3, conv[1].elemsc);
	ASSERT_EQ(1, conv[0].elemsc);
	ASSERT_EQ(2, conv[1].nzelems);
	ASSERT_EQ(1, conv[0].nzelems);

	ASSERT_EQ(2, conv[0].row[0]);
	ASSERT_EQ(4, conv[1].row[0]);
	ASSERT_EQ(0, conv[1].row[1]);
	ASSERT_EQ(66, conv[1].row[2]);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}