#include <gtest/gtest.h>
#include "matrixr.h"

using namespace MatrixR;

TEST (PreTest, natDNum) {
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

TEST(matrTest, mat1) {
	Line *line1 = new Line {3, 0, 0, nullptr, nullptr};
	line1->nextRow = new Line {3, 0, 1, nullptr, nullptr};

	line1->row = new nzel;
	line1->row->number = 4;
	line1->row->position = 0;

	line1->row->next = new nzel;
	line1->row->next->number = 66;
	line1->row->next->position = 2;

	line1->nextRow->row = new nzel;
	line1->nextRow->row->number = 1;
	line1->nextRow->row->position = 0;

	line1->nextRow->row->next = new nzel;
	line1->nextRow->row->next->number = 2;
	line1->nextRow->row->next->position = 1;

	line1->nextRow->row->next->next = new nzel;
	line1->nextRow->row->next->next->number = 3;
	line1->nextRow->row->next->next->position = 2;


	outputM(line1, 3, 2);
	printTable(line1);
	std::cout<<std::endl;

	Line *conv;
	int filr = convertM(conv, line1, 2, 3, 2);
	ASSERT_EQ(0, filr);
	//sortM(conv, 2, 2);

	outputM(conv, 3, 2);
	printTable(conv);
	std::cout<<std::endl;

	ASSERT_EQ(0, conv->number);
	ASSERT_EQ(1, conv->elemsc);
	ASSERT_EQ(1, conv->nzelems);
	ASSERT_EQ(2, conv->row->number);
	ASSERT_EQ(0, conv->row->position);

	ASSERT_EQ(1, conv->nextRow->number);
	ASSERT_EQ(3, conv->nextRow->elemsc);
	ASSERT_EQ(2, conv->nextRow->nzelems);
	ASSERT_EQ(4, conv->nextRow->row->number);
	ASSERT_EQ(0, conv->nextRow->row->position);
	ASSERT_EQ(66, conv->nextRow->row->next->number);
	ASSERT_EQ(2, conv->nextRow->row->next->position);
}

TEST (matrTest, allSpec) {
	Line *line1 = new Line {3, 0, 0, nullptr, nullptr};
	line1->nextRow = new Line {3, 0, 1, nullptr, nullptr};
	line1->nextRow->nextRow = new Line {3, 0, 2, nullptr, nullptr};
	line1->nextRow->nextRow->nextRow = new Line {3, 0, 3, nullptr, nullptr};
	line1->nextRow->nextRow->nextRow->nextRow = new Line {3, 0, 4, nullptr, nullptr};

	line1->row = new nzel {2, 1};

	line1->nextRow->row = new nzel {1, 0};
	line1->nextRow->row->next = new nzel {1, 1};
	line1->nextRow->row->next->next = new nzel {1, 2};

	line1->nextRow->nextRow->row = new nzel {2, 0};
	line1->nextRow->nextRow->row->next = new nzel {2, 1};
	line1->nextRow->nextRow->row->next->next = new nzel {9, 2};

	line1->nextRow->nextRow->nextRow->row = new nzel {5, 1};
	line1->nextRow->nextRow->nextRow->row->next = new nzel {-4, 2};

	line1->nextRow->nextRow->nextRow->nextRow->row = new nzel {1, 1};
	line1->nextRow->nextRow->nextRow->nextRow->row->next = new nzel {-1, 2};

	outputM(line1, 3, 6);
	printTable(line1);
	std::cout<<std::endl;

	Line *conv;
	int filr = convertM(conv, line1, 6, 3, 5);
	ASSERT_EQ(1, filr);

	//sortM(conv, 5, 4);

	outputM(conv, 3, 5);
	printTable(conv);
	std::cout<<std::endl;

	ASSERT_EQ(1, conv->number);
	ASSERT_EQ(1, conv->elemsc);
	ASSERT_EQ(0, conv->nzelems);

	ASSERT_EQ(2, conv->nextRow->number);
	ASSERT_EQ(3, conv->nextRow->elemsc);
	ASSERT_EQ(1, conv->nextRow->nzelems);
	ASSERT_EQ(2, conv->nextRow->row->number);
	ASSERT_EQ(1, conv->nextRow->row->position);

	ASSERT_EQ(3, conv->nextRow->nextRow->number);
	ASSERT_EQ(2, conv->nextRow->nextRow->elemsc);
	ASSERT_EQ(1, conv->nextRow->nextRow->nzelems);
	ASSERT_EQ(-4, conv->nextRow->nextRow->row->number);
	ASSERT_EQ(1, conv->nextRow->nextRow->row->position);

	ASSERT_EQ(4, conv->nextRow->nextRow->nextRow->number);
	ASSERT_EQ(2, conv->nextRow->nextRow->nextRow->elemsc);
	ASSERT_EQ(2, conv->nextRow->nextRow->nextRow->nzelems);
	ASSERT_EQ(2, conv->nextRow->nextRow->nextRow->row->number);
	ASSERT_EQ(0, conv->nextRow->nextRow->nextRow->row->position);
	ASSERT_EQ(2, conv->nextRow->nextRow->nextRow->row->next->number);
	ASSERT_EQ(1, conv->nextRow->nextRow->nextRow->row->next->position);
}


int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}