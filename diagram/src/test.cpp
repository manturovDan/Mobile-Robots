#include <gtest/gtest.h>

#include "diagram.h"

TEST (TestOfTest, Test123) {
	ASSERT_EQ(123, 123);
}

TEST (ConstrTest, commonConstr) {
	timeD::Diagram diag1('X');
	ASSERT_THROW(timeD::Diagram diag3('l'), std::invalid_argument);
	timeD::Diagram diag3('0');
	timeD::Diagram diag4('1');

	ASSERT_EQ(diag1.getLength(), diag1.getSZ());
	ASSERT_EQ(diag1.getSigNum(), 0);

	ASSERT_EQ(diag3.getLength(), diag3.getSZ());
	ASSERT_EQ(diag3.getSigNum(), 1);
	ASSERT_EQ(diag3.getSig(0), 0);

	ASSERT_EQ(diag4.getLength(), diag4.getSZ());
	ASSERT_EQ(diag4.getSigNum(), 1);
	ASSERT_EQ(diag4.getSig(0), 1);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}