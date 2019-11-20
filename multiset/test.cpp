#include <gtest/gtest.h>

#include "multiset.h"

//TODO ZERO CONTAINER
TEST (commonTest, valTest) {
    ASSERT_EQ(1, 1);
}

TEST (iterTest, startingTest) {
    std::dmultiset<int> mset;
    mset.insert(1);
    mset.insert(2);
    mset.insert(-50);


    ASSERT_NO_THROW(std::dmultiset<int>::iterator iterrr);

    ASSERT_EQ(*(mset.begin()), -50);
}

TEST(constTest, copyConstr) {
    std::dmultiset<float> m_set_1;
    m_set_1.insert({.1, 5.28, -64.1, 12, 53, 19, 81, 33, 9});

    std::dmultiset<float> m_set_2(m_set_1);

    ASSERT_EQ(m_set_1.count(), m_set_2.count());
    m_set_2.printTree();
    std::dmultiset<float>::const_iterator i = m_set_2.begin();
    ASSERT_FLOAT_EQ(*i, -64.1);
    i++;
    ASSERT_FLOAT_EQ(*i, 0.1);
    i++;
    ASSERT_FLOAT_EQ(*i, 5.28);
    i++;
    ASSERT_FLOAT_EQ(*i, 9);
    i++;
    ASSERT_FLOAT_EQ(*i, 12);
    i++;
    ASSERT_FLOAT_EQ(*i, 19);
    i++;
    ASSERT_FLOAT_EQ(*i, 33);
    i++;
    ASSERT_FLOAT_EQ(*i, 53);
    i++;
    ASSERT_FLOAT_EQ(*i, 81);
    i++;
    ASSERT_EQ(i, m_set_2.end());
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

TEST (iterTest, fwIter) {
    std::dmultiset<float> m_set_i;

    float addVals[] = {.1, 5.28, -64.1, 12, 53, 19, 81, 33, 9};

    int cntEls = sizeof(addVals)/sizeof(addVals[0]);;
    for (int i = 0; i < cntEls; i++)
        m_set_i.insert(addVals[i]);

    std::sort(addVals, addVals+cntEls);

    int it = 0;
    for(std::dmultiset<float>::iterator i = m_set_i.begin(); i != m_set_i.end(); i++) {
        ASSERT_FLOAT_EQ(*i, addVals[it]);
        it++;
    }
}

TEST (iterTest, constFwIter) {
    std::dmultiset<float> m_set_i;

    float addVals[] = {.1, 5.28, -64.1, 12, 53, 19, 81, 33, 9};

    int cntEls = sizeof(addVals)/sizeof(addVals[0]);;
    for (int i = 0; i < cntEls; i++)
        m_set_i.insert(addVals[i]);

    std::sort(addVals, addVals+cntEls);

    int it = 0;
    for(std::dmultiset<float>::const_iterator i = m_set_i.cbegin(); i != m_set_i.cend(); i++) {
        ASSERT_FLOAT_EQ(*i, addVals[it]);
        it++;
    }
}

TEST (iterTest, backIter) {
    std::dmultiset<float> m_set_i;

    float addVals[] = {.1, 5.28, -64.1, 12, 53, 19, 81, 33, 9};

    int cntEls = sizeof(addVals)/sizeof(addVals[0]);;
    for (int i = 0; i < cntEls; i++)
        m_set_i.insert(addVals[i]);

    std::sort(addVals, addVals+cntEls);
    std::reverse(addVals, addVals+cntEls);

    int it = 0;
    for(std::dmultiset<float>::reverse_iterator i = m_set_i.rbegin(); i != m_set_i.rend(); i++) {
        ASSERT_FLOAT_EQ(*i, addVals[it]);
        it++;
    }
}

TEST (iterTest, constBackIter) {
    std::dmultiset<float> m_set_i;

    float addVals[] = {.1, 5.28, -64.1, 12, 53, 19, 81, 33, 9};

    int cntEls = sizeof(addVals)/sizeof(addVals[0]);;
    for (int i = 0; i < cntEls; i++)
        m_set_i.insert(addVals[i]);

    std::sort(addVals, addVals+cntEls);
    std::reverse(addVals, addVals+cntEls);

    int it = 0;
    for(std::dmultiset<float>::reverse_iterator i = m_set_i.crbegin(); i != m_set_i.crend(); i++) {
        ASSERT_FLOAT_EQ(*i, addVals[it]);
        it++;
    }
}

TEST (modifierTest, iterInsert) {
    std::dmultiset<float> m_set_i;
    std::vector<float> vect = {.1, 5.28, -64.1, 12, 53, 19, 81, 33, 9};

    m_set_i.insert(vect.begin()+1, vect.begin()+5);

    ASSERT_EQ(m_set_i.count(), 4);
    std::dmultiset<float>::const_iterator i = m_set_i.begin();
    ASSERT_FLOAT_EQ(*i, -64.1);
    i++;
    ASSERT_FLOAT_EQ(*i, 5.28);
    i++;
    ASSERT_FLOAT_EQ(*i, 12);
    i++;
    ASSERT_FLOAT_EQ(*i, 53);
    i++;
    ASSERT_EQ(i, m_set_i.end());
}

TEST (modifierTest, initInsert) {
    std::dmultiset<float> m_set_i;
    m_set_i.insert({.1, 5.28, -64.1, 12, 53, 19, 81, 33, 9});

    ASSERT_EQ(m_set_i.count(), 9);
    std::dmultiset<float>::const_iterator i = m_set_i.begin();
    ASSERT_FLOAT_EQ(*i, -64.1);
    i++;
    ASSERT_FLOAT_EQ(*i, 0.1);
    i++;
    ASSERT_FLOAT_EQ(*i, 5.28);
    i++;
    ASSERT_FLOAT_EQ(*i, 9);
    i++;
    ASSERT_FLOAT_EQ(*i, 12);
    i++;
    ASSERT_FLOAT_EQ(*i, 19);
    i++;
    ASSERT_FLOAT_EQ(*i, 33);
    i++;
    ASSERT_FLOAT_EQ(*i, 53);
    i++;
    ASSERT_FLOAT_EQ(*i, 81);
    i++;
    ASSERT_EQ(i, m_set_i.end());
}

TEST (modifierTest, eraseTop) {
    std::dmultiset<float> m_set_i;
    m_set_i.insert({.1, 5.28, -64.1, 12, 53, 19, 81, 33, 9});

    std::dmultiset<float>::const_iterator delt = m_set_i.erase(++m_set_i.begin());

    ASSERT_EQ(m_set_i.count(), 8);

    std::dmultiset<float>::const_iterator i = m_set_i.begin();

    ASSERT_FLOAT_EQ(*delt, 5.28);

    ASSERT_FLOAT_EQ(*i, -64.1);
    i++;
    ASSERT_FLOAT_EQ(*i, 5.28);
    i++;
    ASSERT_FLOAT_EQ(*i, 9);
    i++;
    ASSERT_FLOAT_EQ(*i, 12);
    i++;
    ASSERT_FLOAT_EQ(*i, 19);
    i++;
    ASSERT_FLOAT_EQ(*i, 33);
    i++;
    ASSERT_FLOAT_EQ(*i, 53);
    i++;
    ASSERT_FLOAT_EQ(*i, 81);
    i++;
    ASSERT_EQ(i, m_set_i.end());
}

TEST (lookupTest, search) {
    std::dmultiset<float> m_set_i;
    m_set_i.insert({.1, 5.28, -64.1, 12, 53, 19, 81, 33, 9});

    std::dmultiset<float>::const_iterator found = m_set_i.find(9);
    ASSERT_EQ(*found, 9);
}


TEST (lookupTest, multiSearch) {
    std::dmultiset<float> m_set_i;
    m_set_i.insert({.1, 5.28, 19, -64.1, 12, 53, 19, 81, 33, 9, 19});

    std::dmultiset<float>::const_iterator found = m_set_i.find(19);
    ASSERT_EQ(*found, 19);
    found++;
    ASSERT_FLOAT_EQ(*found, 19);
    found++;
    ASSERT_FLOAT_EQ(*found, 19);
    found++;
    ASSERT_NE(*found, 19);
}

/*TEST(modifierTest, clearTree) {
    std::dmultiset<float> m_set_i;
    m_set_i.insert({.1, 5.28, 19, -64.1, 12, 53, 19, 81, 33, 9, 19});
    m_set_i.clear();

    std::cout << *m_set_i.begin() << std::endl;

    ASSERT_EQ(m_set_i.count(), 0);
}*/

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}