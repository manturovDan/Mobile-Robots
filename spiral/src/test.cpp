#include <gtest/gtest.h>

#include "aspiral.h"

TEST (helloTest, Test) {
	ASSERT_EQ(123, 123);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}