#include <gtest/gtest.h>
#include "matrixr.h"

using namespace MatrixR;

/*TEST (PreTest, natDNum) {
	ASSERT_EQ(0, evenDNum(12));
	ASSERT_EQ(1, evenDNum(22));
	ASSERT_EQ(1, evenDNum(0));
	ASSERT_EQ(0, evenDNum(12222));
	ASSERT_EQ(1, evenDNum(4440));
	ASSERT_EQ(0, evenDNum(-6554));
	ASSERT_EQ(1, evenDNum(6080606));
	ASSERT_EQ(1, evenDNum(-2000088));
	ASSERT_EQ(0, evenDNum(121111));
	ASSERT_EQ(1, evenDNum(404));
	ASSERT_EQ(0, evenDNum(-1));
	ASSERT_EQ(0, evenDNum(-7794955));
	ASSERT_EQ(0, evenDNum(210888));
	ASSERT_EQ(1, evenDNum(-42604));
	ASSERT_EQ(0, evenDNum(1000000));
}

TEST (matrTest, mat1) {
	int *row1 = new int[3] {4, 0, 66};
	int *row2 = new int[3] {1, 2, 3};

	Line *lines = new Line[2] {{3, 0, row1}, {3, 0, row2}};
	//outputM("Test", lines, 2);
	
	int rows_c;
	Line *conv = filterM(lines, 2, rows_c);
	//outputM("TestC", conv, 2);

	ASSERT_EQ(2, rows_c);
	ASSERT_EQ(3, conv[0].elemsc);
	ASSERT_EQ(1, conv[1].elemsc);
	ASSERT_EQ(2, conv[0].nzelems);
	ASSERT_EQ(1, conv[1].nzelems);

	sortM(conv, rows_c);
	//outputM("TestS", conv, 2);
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

TEST (matrTest, mat2delrow) {
	int *row1 = new int[3] {4, 0, 66};
	int *row2 = new int[3] {1, 1, 1};
	int *row3 = new int[3] {1, 2, 3};

	Line *lines = new Line[3] {{3, 0, row1}, {3, 0, row2}, {3, 0, row3}};
	//outputM("Test", lines, 3);
	
	int rows_c;
	Line *conv = filterM(lines, 3, rows_c);
	//outputM("TestC", conv, 2);

	ASSERT_EQ(2, rows_c);
	ASSERT_EQ(3, conv[0].elemsc);
	ASSERT_EQ(1, conv[1].elemsc);
	ASSERT_EQ(2, conv[0].nzelems);
	ASSERT_EQ(1, conv[1].nzelems);

	sortM(conv, rows_c);
	//outputM("TestS", conv, 2);
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

TEST (matrTest, mat3delLastRowCompl) {
	int *row1 = new int[6] {0, 9, 12, 22, 44, 88};
	int *row2 = new int[6] {0, 0, 0, 2, 3, 404};
	int *row3 = new int[6] {-972, 2, -44, 68000, 21, 46};
	int *row4 = new int[6] {0, 1, 0, 0, 0, 0};
	int *row5 = new int[6] {1, 1, 1, 3, -1, -10002};

	Line *lines = new Line[5] {{6, 0, row1}, {6, 0, row2}, {6, 0, row3}, {6, 0, row4}, {6, 0, row5}};
	//outputM("Test", lines, 5);
	
	int rows_c;
	Line *conv = filterM(lines, 6, rows_c);
	//outputM("TestC", conv, 4);

	ASSERT_EQ(4, rows_c);
	ASSERT_EQ(4, conv[0].elemsc);
	ASSERT_EQ(5, conv[1].elemsc);
	ASSERT_EQ(4, conv[2].elemsc);
	ASSERT_EQ(5, conv[3].elemsc);

	ASSERT_EQ(3, conv[0].nzelems);
	ASSERT_EQ(2, conv[1].nzelems);
	ASSERT_EQ(4, conv[2].nzelems);
	ASSERT_EQ(0, conv[3].nzelems);

	ASSERT_EQ(0, conv[0].row[0]);
	ASSERT_EQ(22, conv[0].row[1]);
	ASSERT_EQ(44, conv[0].row[2]);
	ASSERT_EQ(88, conv[0].row[3]);

	ASSERT_EQ(0, conv[1].row[0]);
	ASSERT_EQ(0, conv[1].row[1]);
	ASSERT_EQ(0, conv[1].row[2]);
	ASSERT_EQ(2, conv[1].row[3]);
	ASSERT_EQ(404, conv[1].row[4]);

	ASSERT_EQ(2, conv[2].row[0]);
	ASSERT_EQ(-44, conv[2].row[1]);
	ASSERT_EQ(68000, conv[2].row[2]);
	ASSERT_EQ(46, conv[2].row[3]);

	ASSERT_EQ(0, conv[3].row[0]);
	ASSERT_EQ(0, conv[3].row[1]);
	ASSERT_EQ(0, conv[3].row[2]);
	ASSERT_EQ(0, conv[3].row[3]);
	ASSERT_EQ(0, conv[3].row[4]);

	sortM(conv, rows_c);
	//outputM("TestS", conv, 4);
	ASSERT_EQ(4, rows_c);
	ASSERT_EQ(5, conv[0].elemsc);
	ASSERT_EQ(5, conv[1].elemsc);
	ASSERT_EQ(4, conv[2].elemsc);
	ASSERT_EQ(4, conv[3].elemsc);

	ASSERT_EQ(0, conv[0].nzelems);
	ASSERT_EQ(2, conv[1].nzelems);
	ASSERT_EQ(3, conv[2].nzelems);
	ASSERT_EQ(4, conv[3].nzelems);

	ASSERT_EQ(0, conv[2].row[0]);
	ASSERT_EQ(22, conv[2].row[1]);
	ASSERT_EQ(44, conv[2].row[2]);
	ASSERT_EQ(88, conv[2].row[3]);

	ASSERT_EQ(0, conv[1].row[0]);
	ASSERT_EQ(0, conv[1].row[1]);
	ASSERT_EQ(0, conv[1].row[2]);
	ASSERT_EQ(2, conv[1].row[3]);
	ASSERT_EQ(404, conv[1].row[4]);

	ASSERT_EQ(2, conv[3].row[0]);
	ASSERT_EQ(-44, conv[3].row[1]);
	ASSERT_EQ(68000, conv[3].row[2]);
	ASSERT_EQ(46, conv[3].row[3]);

	ASSERT_EQ(0, conv[0].row[0]);
	ASSERT_EQ(0, conv[0].row[1]);
	ASSERT_EQ(0, conv[0].row[2]);
	ASSERT_EQ(0, conv[0].row[3]);
	ASSERT_EQ(0, conv[0].row[4]);
}

TEST (matrTest, mat4delFRow) {
	int *row1 = new int[3] {1, 3, -227}; //must be deleted
	int *row2 = new int[3] {5, 0, 0};
	int *row3 = new int[3] {2, 2, 9};
	int *row4 = new int[3] {0, 0, 0};

	Line *lines = new Line[4] {{3, 0, row1}, {3, 0, row2}, {3, 0, row3}, {3, 0, row4}};
	//outputM("Test", lines, 5);
	
	int rows_c;
	Line *conv = filterM(lines, 4, rows_c);
	//outputM("TestC", conv, 3);

	ASSERT_EQ(3, rows_c);
	ASSERT_EQ(2, conv[0].elemsc);
	ASSERT_EQ(2, conv[1].elemsc);
	ASSERT_EQ(3, conv[2].elemsc);

	ASSERT_EQ(0, conv[0].nzelems);
	ASSERT_EQ(2, conv[1].nzelems);
	ASSERT_EQ(0, conv[2].nzelems);

	ASSERT_EQ(0, conv[0].row[0]);
	ASSERT_EQ(0, conv[0].row[1]);

	ASSERT_EQ(2, conv[1].row[0]);
	ASSERT_EQ(2, conv[1].row[1]);

	ASSERT_EQ(0, conv[2].row[0]);
	ASSERT_EQ(0, conv[2].row[1]);
	ASSERT_EQ(0, conv[2].row[2]);

	sortM(conv, rows_c);
	//outputM("TestS", conv, 3);
	ASSERT_EQ(3, rows_c);
	ASSERT_EQ(2, conv[0].elemsc);
	ASSERT_EQ(2, conv[2].elemsc);
	ASSERT_EQ(3, conv[1].elemsc);

	ASSERT_EQ(0, conv[0].nzelems);
	ASSERT_EQ(2, conv[2].nzelems);
	ASSERT_EQ(0, conv[1].nzelems);

	ASSERT_EQ(0, conv[0].row[0]);
	ASSERT_EQ(0, conv[0].row[1]);

	ASSERT_EQ(2, conv[2].row[0]);
	ASSERT_EQ(2, conv[2].row[1]);

	ASSERT_EQ(0, conv[1].row[0]);
	ASSERT_EQ(0, conv[1].row[1]);
	ASSERT_EQ(0, conv[1].row[2]);

}

TEST (specifyTest, empResMatr) {
	int *row1 = new int[2] {1, 19};
	int *row2 = new int[2] {1, -1};
	
	Line *lines = new Line[2] {{2, 0, row1}, {2, 0, row2}};
	
	int rows_c;
	Line *conv = filterM(lines, 2, rows_c);
	ASSERT_EQ(0, rows_c);
}*/

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}