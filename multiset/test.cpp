#include <gtest/gtest.h>

#include "multiset.h"

TEST (commonTest, valTest) {
    ASSERT_EQ(1, 1);
}

TEST (iterTest, BeginEndTest) {
    std::dmultiset<int> mset;
    mset.insert(1);
    mset.insert(2);
    mset.insert(-50);

    mset.printTree();

    std::dmultiset<int>::iterator iterrr;

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}