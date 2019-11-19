#include <gtest/gtest.h>

#include "multiset.h"

TEST (commonTest, valTest) {
    ASSERT_EQ(1, 1);
}

TEST (iterTest, startingTest) {
    std::dmultiset<int> mset;
    mset.insert(1);
    mset.insert(2);
    mset.insert(-50);


    std::dmultiset<int>::iterator iterrr;

    ASSERT_EQ(*(mset.begin()), -50);
}

TEST (iterTest, forwardIteratorTest) {
    std::dmultiset<int> m_set_i;
    std::dmultiset<int>::iterator fw_iter;

    m_set_i.insert(-50);
    m_set_i.insert(1);
    m_set_i.insert(675);
    m_set_i.insert(0);
    m_set_i.insert(-657);


    fw_iter = m_set_i.begin();
    ASSERT_EQ(*(m_set_i.begin()), -657);
    ASSERT_EQ(*(fw_iter++), -657);
    ASSERT_EQ(*fw_iter, -50);
    ASSERT_EQ(*(++fw_iter), 0);

    ASSERT_EQ(*(m_set_i.begin()++), -657);
    ASSERT_EQ(*(m_set_i.begin()), -657);
    ASSERT_EQ(*(++m_set_i.begin()), -50);
    ASSERT_EQ(*(m_set_i.begin()), -657);

    ASSERT_EQ(*(++ ++fw_iter), 675);
    ASSERT_EQ(*fw_iter, 675);

    ++fw_iter;
    ASSERT_THROW(*fw_iter, std::invalid_argument);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}