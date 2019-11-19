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

    //mset.printTree();

    std::dmultiset<int>::iterator iterrr;

    ASSERT_EQ(*(mset.begin()), -50);
}

TEST (iterTest, forwardIteratorTest) {
    std::dmultiset<int> m_set_i;
    std::dmultiset<int>::iterator fw_iter;

    m_set_i.insert(1);
    m_set_i.insert(2);
    m_set_i.insert(-50);
    m_set_i.insert(1);
    m_set_i.insert(675);
    m_set_i.insert(75);
    m_set_i.insert(0);
    m_set_i.insert(755);
    m_set_i.insert(-657);
    m_set_i.insert(879);
    m_set_i.insert(54);
    m_set_i.insert(44);
    m_set_i.insert(234);
    m_set_i.insert(503);
    m_set_i.insert(54320);
    m_set_i.insert(450);


    fw_iter = m_set_i.begin();
    ASSERT_EQ(*(m_set_i.begin()), -657);
    ASSERT_EQ(*(fw_iter++), -657);
    ASSERT_EQ(*fw_iter, -50);


}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}