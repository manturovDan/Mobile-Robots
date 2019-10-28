#include <gtest/gtest.h>

#include "diagram.h"

TEST (ConstrTest, ASCIItest) {
    char str[] = "010101001XXX000X1111";
    char str2[] = "0110XXX0010";
    timeD::Diagram diag1(str);
    timeD::Diagram diag2(str2);

    ASSERT_EQ(diag1.getScale(), 1);
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

    ASSERT_EQ(diag2.getScale(), 1);
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

    ASSERT_EQ(diag1.getSigNum(), 0);

    ASSERT_EQ(diag3.getSigNum(), 1);
    ASSERT_EQ(diag3.getSig(0), 0);

    ASSERT_EQ(diag4.getSigNum(), 1);
    ASSERT_EQ(diag4.getSig(0), 1);
}


TEST (intfTest, addSig) {
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
    ASSERT_THROW(diag1.addSignal('X', 1e9, 3), std::invalid_argument);
    ASSERT_THROW(diag1.addSignal('X', 15, 1e9), std::invalid_argument);

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

    ASSERT_EQ(diag1.getScale(), 1);
}

TEST (intfTest, uniTest) {
    timeD::Diagram diag1;
    timeD::Diagram diag2;

    diag1.addSignal('0', 5, 7);
    diag1.addSignal('1', 12, 14);

    diag2.addSignal('0', 3, 1);
    diag2.addSignal('1', 4, 8);
    diag2.addSignal('0', 12, 5);

    ASSERT_NO_THROW(diag1 += diag2);
    ASSERT_EQ(diag1.getScale(), 1);
    ASSERT_EQ(diag2.getScale(), 1);

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

    ASSERT_NO_THROW(diag2 += diag2);

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

    ASSERT_NO_THROW(diag2 += diag2);

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
}

TEST(intfTest, unitTestMulty) {
    timeD::Diagram diag1("100101XXX11");
    timeD::Diagram diag2("1000XXX010110");
    timeD::signal conc1[] = {{1, 0, 1}, {0, 1, 2}, {1, 3, 1}, {0, 4, 1}, {1, 5, 1},
                             {1, 9, 3}, {0, 12, 3}, {0, 18, 1},
                             {1, 19, 1}, {0, 20, 1}, {1, 21, 2}, {0, 23, 1}};
    timeD::signal conc2[] = {{1, 0, 1}, {0, 1, 3}, {0, 7, 1}, {1, 8, 1},
                             {0, 9, 1}, {1, 10, 2}, {0, 12, 1}};

    ASSERT_NO_THROW(diag1 += diag2 += diag1 += diag2);

    ASSERT_EQ(diag2.getSigNum(), 19);
    ASSERT_EQ(diag2.getScale(), 2);
    ASSERT_EQ(diag2.getLength(), 37);
    for (int i = 0; i < 7; ++i) {
        //std:: cout << i <<" - " << diag2.getSig(i) << " - " << conc2[i].val << std::endl;
        ASSERT_EQ(diag2.getSig(i), conc2[i].val);
        ASSERT_EQ(diag2.getSigStart(i), conc2[i].start);
        ASSERT_EQ(diag2.getSigLen(i), conc2[i].length);
    }
    for (int i = 7; i < 19; ++i) {
        ASSERT_EQ(diag2.getSig(i), conc1[i - 7].val);
        ASSERT_EQ(diag2.getSigStart(i), conc1[i - 7].start + 13);
        ASSERT_EQ(diag2.getSigLen(i), conc1[i - 7].length);
    }


    ASSERT_EQ(diag1.getSigNum(), 31);
    ASSERT_EQ(diag1.getScale(), 4);
    ASSERT_EQ(diag1.getLength(), 61);
    for (int i = 0; i < 12; ++i) {
        ASSERT_EQ(diag1.getSig(i), conc1[i].val);
        ASSERT_EQ(diag1.getSigStart(i), conc1[i].start);
        ASSERT_EQ(diag1.getSigLen(i), conc1[i].length);
    }
    for (int i = 12; i < 19; ++i) {
        ASSERT_EQ(diag1.getSig(i), conc2[i - 12].val);
        ASSERT_EQ(diag1.getSigStart(i), conc2[i - 12].start + 24);
        ASSERT_EQ(diag1.getSigLen(i), conc2[i - 12].length);
    }
    for (int i = 19; i < 31; ++i) {
        ASSERT_EQ(diag1.getSig(i), conc1[i - 19].val);
        ASSERT_EQ(diag1.getSigStart(i), conc1[i - 19].start + 37);
        ASSERT_EQ(diag1.getSigLen(i), conc1[i - 19].length);
    }

}

TEST (intfTest, uniTestPrefPP) {
    timeD::Diagram diag2;
    timeD::Diagram diag3;


    diag2.addSignal('0', 3, 1);
    diag2.addSignal('1', 4, 8);
    diag2.addSignal('0', 12, 5);

    diag3 = ++diag2;

    ASSERT_EQ(diag2.getScale(), 1);
    ASSERT_EQ(diag2.getLength(), 34);
    ASSERT_EQ(diag2.getSigNum(), 6);

    ASSERT_EQ(diag3.getLength(), 34);
    ASSERT_EQ(diag3.getSigNum(), 6);

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

    ASSERT_EQ(diag3.getSig(0), 0);
    ASSERT_EQ(diag3.getSigStart(0), 3);
    ASSERT_EQ(diag3.getSigLen(0), 1);

    ASSERT_EQ(diag3.getSig(1), 1);
    ASSERT_EQ(diag3.getSigStart(1), 4);
    ASSERT_EQ(diag3.getSigLen(1), 8);

    ASSERT_EQ(diag3.getSig(2), 0);
    ASSERT_EQ(diag3.getSigStart(2), 12);
    ASSERT_EQ(diag3.getSigLen(2), 5);

    ASSERT_EQ(diag3.getSig(3), 0);
    ASSERT_EQ(diag3.getSigStart(3), 20);
    ASSERT_EQ(diag3.getSigLen(3), 1);

    ASSERT_EQ(diag3.getSig(4), 1);
    ASSERT_EQ(diag3.getSigStart(4), 21);
    ASSERT_EQ(diag3.getSigLen(4), 8);

    ASSERT_EQ(diag3.getSig(5), 0);
    ASSERT_EQ(diag3.getSigStart(5), 29);
    ASSERT_EQ(diag3.getSigLen(5), 5);

}

TEST (intfTest, uniTestPostPP) {
    timeD::Diagram diag2;
    timeD::Diagram diag3;


    diag2.addSignal('0', 0, 1);
    diag2.addSignal('1', 4, 8);
    diag2.addSignal('0', 12, 5);

    diag3 = diag2++;

    ASSERT_EQ(diag2.getScale(), 1);
    ASSERT_EQ(diag2.getLength(), 34);
    ASSERT_EQ(diag2.getSigNum(), 5);

    ASSERT_EQ(diag2.getSig(0), 0);
    ASSERT_EQ(diag2.getSigStart(0), 0);
    ASSERT_EQ(diag2.getSigLen(0), 1);

    ASSERT_EQ(diag2.getSig(1), 1);
    ASSERT_EQ(diag2.getSigStart(1), 4);
    ASSERT_EQ(diag2.getSigLen(1), 8);

    ASSERT_EQ(diag2.getSig(2), 0);
    ASSERT_EQ(diag2.getSigStart(2), 12);
    ASSERT_EQ(diag2.getSigLen(2), 6);

    ASSERT_EQ(diag2.getSig(3), 1);
    ASSERT_EQ(diag2.getSigStart(3), 21);
    ASSERT_EQ(diag2.getSigLen(3), 8);

    ASSERT_EQ(diag2.getSig(4), 0);
    ASSERT_EQ(diag2.getSigStart(4), 29);
    ASSERT_EQ(diag2.getSigLen(4), 6);

    ASSERT_EQ(diag3.getLength(), 17);
    ASSERT_EQ(diag3.getSigNum(), 3);

    ASSERT_EQ(diag3.getSig(0), 0);
    ASSERT_EQ(diag3.getSigStart(0), 0);
    ASSERT_EQ(diag3.getSigLen(0), 1);

    ASSERT_EQ(diag3.getSig(1), 1);
    ASSERT_EQ(diag3.getSigStart(1), 4);
    ASSERT_EQ(diag3.getSigLen(1), 8);

    ASSERT_EQ(diag3.getSig(2), 0);
    ASSERT_EQ(diag3.getSigStart(2), 12);
    ASSERT_EQ(diag3.getSigLen(2), 5);
}

TEST (intfTest, uniTestPostPPMult) {
    timeD::Diagram diag2;
    timeD::Diagram diag3;

    diag2.addSignal('0', 1, 1);
    diag2.addSignal('1', 4, 2);
    diag2.addSignal('0', 7, 2);

    timeD::signal checker[] {{0, 1, 1}, {1, 4, 2}, {0, 7, 2},
                             {0, 10, 1}, {1, 13, 2}, {0, 16, 2},
                             {0, 19, 1}, {1, 22, 2}, {0, 25, 2},
                             {0, 28, 1}, {1, 31, 2},  {0, 34, 2},
                             {0, 37, 1}, {1, 40, 2}, {0, 43, 2},
                             {0, 46, 1}, {1, 49, 2}, {0, 52, 2},
                             {0, 55, 1}, {1, 58, 2}, {0, 61, 2},
                             {0, 64, 1}, {1, 67, 2}, {0, 70, 2}};


    ASSERT_NO_THROW(diag3 = ++ ++ ++ diag2);

    ASSERT_EQ(diag2.getScale(), 3);
    ASSERT_EQ(diag2.getLength(), 72);
    ASSERT_EQ(diag2.getSigNum(), 24);
    for (int i = 0; i < 24; ++i) {
        //std:: cout << i <<" - " << diag2.getSig(i) << " - " << checker[i].val << std::endl;
        ASSERT_EQ(diag2.getSig(i), checker[i].val);
        ASSERT_EQ(diag2.getSigStart(i), checker[i].start);
        ASSERT_EQ(diag2.getSigLen(i), checker[i].length);
    }


    ASSERT_EQ(diag3.getScale(), 3);
    ASSERT_EQ(diag3.getLength(), 72);
    ASSERT_EQ(diag3.getSigNum(), 24);
    for (int i = 0; i < 24; ++i) {
        //std:: cout << i <<" - " << diag2.getSig(i) << " - " << checker[i].val << std::endl;
        ASSERT_EQ(diag3.getSig(i), checker[i].val);
        ASSERT_EQ(diag3.getSigStart(i), checker[i].start);
        ASSERT_EQ(diag3.getSigLen(i), checker[i].length);
    }

}


TEST (intfTest, uniTestGluing) {
    timeD::Diagram diag1;
    timeD::Diagram diag2;

    diag1.addSignal('1', 5, 7);
    diag1.addSignal('0', 12, 4);

    diag2.addSignal('0', 0, 1);
    diag2.addSignal('1', 4, 8);
    diag2.addSignal('0', 12, 5);

    diag1 += diag2;

    ASSERT_EQ(diag1.getLength(), 33);
    ASSERT_EQ(diag1.getScale(), 1);
    ASSERT_EQ(diag1.getSigNum(), 4);

    ASSERT_EQ(diag1.getSig(0), 1);
    ASSERT_EQ(diag1.getSigStart(0), 5);
    ASSERT_EQ(diag1.getSigLen(0), 7);

    ASSERT_EQ(diag1.getSig(1), 0);
    ASSERT_EQ(diag1.getSigStart(1), 12);
    ASSERT_EQ(diag1.getSigLen(1), 5);

    ASSERT_EQ(diag1.getSig(2), 1);
    ASSERT_EQ(diag1.getSigStart(2), 20);
    ASSERT_EQ(diag1.getSigLen(2), 8);

    ASSERT_EQ(diag1.getSig(3), 0);
    ASSERT_EQ(diag1.getSigStart(3), 28);
    ASSERT_EQ(diag1.getSigLen(3), 5);
}

TEST (intfTest, uniTestAddition) {
    timeD::Diagram diag1;
    timeD::Diagram diag2;
    timeD::Diagram diag3;

    diag1.addSignal('1', 5, 7);
    diag1.addSignal('0', 12, 4);

    diag2.addSignal('0', 0, 1);
    diag2.addSignal('1', 4, 8);
    diag2.addSignal('0', 12, 5);

    diag3 = diag1 + diag2;

    ASSERT_EQ(diag3.getLength(), 33);
    ASSERT_EQ(diag3.getSigNum(), 4);

    ASSERT_EQ(diag3.getSig(0), 1);
    ASSERT_EQ(diag3.getSigStart(0), 5);
    ASSERT_EQ(diag3.getSigLen(0), 7);

    ASSERT_EQ(diag3.getSig(1), 0);
    ASSERT_EQ(diag3.getSigStart(1), 12);
    ASSERT_EQ(diag3.getSigLen(1), 5);

    ASSERT_EQ(diag3.getSig(2), 1);
    ASSERT_EQ(diag3.getSigStart(2), 20);
    ASSERT_EQ(diag3.getSigLen(2), 8);

    ASSERT_EQ(diag3.getSig(3), 0);
    ASSERT_EQ(diag3.getSigStart(3), 28);
    ASSERT_EQ(diag3.getSigLen(3), 5);

    ASSERT_EQ(diag1.getLength(), 16);
    ASSERT_EQ(diag1.getSigNum(), 2);

    ASSERT_EQ(diag2.getLength(), 17);
    ASSERT_EQ(diag2.getSigNum(), 3);
}

TEST (intfTest, uniTestAdditionConv) {
    timeD::Diagram diag2;
    timeD::Diagram diag3;

    timeD::Diagram diag1("XXXXX11111110000");

    diag2.addSignal('0', 0, 1);
    diag2.addSignal('1', 4, 8);
    diag2.addSignal('0', 12, 5);

    diag3 = diag1 + diag2;

    ASSERT_EQ(diag3.getLength(), 33);
    ASSERT_EQ(diag3.getSigNum(), 4);

    ASSERT_EQ(diag3.getSig(0), 1);
    ASSERT_EQ(diag3.getSigStart(0), 5);
    ASSERT_EQ(diag3.getSigLen(0), 7);

    ASSERT_EQ(diag3.getSig(1), 0);
    ASSERT_EQ(diag3.getSigStart(1), 12);
    ASSERT_EQ(diag3.getSigLen(1), 5);

    ASSERT_EQ(diag3.getSig(2), 1);
    ASSERT_EQ(diag3.getSigStart(2), 20);
    ASSERT_EQ(diag3.getSigLen(2), 8);

    ASSERT_EQ(diag3.getSig(3), 0);
    ASSERT_EQ(diag3.getSigStart(3), 28);
    ASSERT_EQ(diag3.getSigLen(3), 5);

    ASSERT_EQ(diag1.getLength(), 16);
    ASSERT_EQ(diag1.getSigNum(), 2);

    ASSERT_EQ(diag2.getLength(), 17);
    ASSERT_EQ(diag2.getSigNum(), 3);
}

TEST (intfTest, copyTestSimp) {
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

    ASSERT_EQ(diag2.copyDiagram(diag2.getMaxSig() / diag2.getSigNum() + 10), 1);
    ASSERT_EQ(diag2.copyDiagram(diag2.getMaxLen() / diag2.getLength() + 10), 1);

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

TEST (intfTest, copyGluingTest) {
    timeD::Diagram diag1;

    diag1.addSignal('0', 0, 2);
    diag1.addSignal('1', 2, 3);
    diag1.addSignal('0', 6, 1);

    diag1.copyDiagram(5);

    ASSERT_EQ(diag1.getLength(), 35);
    ASSERT_EQ(diag1.getSigNum(), 11);

    ASSERT_EQ(diag1.getSig(0), 0);
    ASSERT_EQ(diag1.getSigStart(0), 0);
    ASSERT_EQ(diag1.getSigLen(0), 2);

    ASSERT_EQ(diag1.getSig(1), 1);
    ASSERT_EQ(diag1.getSigStart(1), 2);
    ASSERT_EQ(diag1.getSigLen(1), 3);

    ASSERT_EQ(diag1.getSig(2), 0);
    ASSERT_EQ(diag1.getSigStart(2), 6);
    ASSERT_EQ(diag1.getSigLen(2), 3);

    ASSERT_EQ(diag1.getSig(3), 1);
    ASSERT_EQ(diag1.getSigStart(3), 9);
    ASSERT_EQ(diag1.getSigLen(4), 3);

    ASSERT_EQ(diag1.getSig(4), 0);
    ASSERT_EQ(diag1.getSigStart(4), 13);
    ASSERT_EQ(diag1.getSigLen(4), 3);

    ASSERT_EQ(diag1.getSig(5), 1);
    ASSERT_EQ(diag1.getSigStart(5), 16);
    ASSERT_EQ(diag1.getSigLen(5), 3);

    ASSERT_EQ(diag1.getSig(6), 0);
    ASSERT_EQ(diag1.getSigStart(6), 20);
    ASSERT_EQ(diag1.getSigLen(6), 3);

    ASSERT_EQ(diag1.getSig(7), 1);
    ASSERT_EQ(diag1.getSigStart(7), 23);
    ASSERT_EQ(diag1.getSigLen(7), 3);

    ASSERT_EQ(diag1.getSig(8), 0);
    ASSERT_EQ(diag1.getSigStart(8), 27);
    ASSERT_EQ(diag1.getSigLen(8), 3);

    ASSERT_EQ(diag1.getSig(9), 1);
    ASSERT_EQ(diag1.getSigStart(9), 30);
    ASSERT_EQ(diag1.getSigLen(9), 3);

    ASSERT_EQ(diag1.getSig(10), 0);
    ASSERT_EQ(diag1.getSigStart(10), 34);
    ASSERT_EQ(diag1.getSigLen(10), 1);

    ASSERT_EQ(diag1.getScale(), 2);
}

TEST (noShiftTest, intfTest) {
    timeD::Diagram diag1;
    timeD::Diagram diag2;
    diag1.addSignal('0', 5, 7);
    diag1.addSignal('1', 12, 14);

    diag2.addSignal('0', 3, 1);
    diag2.addSignal('1', 4, 8);
    diag2.addSignal('0', 12, 5);

    ASSERT_NO_THROW(diag1 += diag2);

    diag1<<0;

    ASSERT_THROW(diag1<<(-5), std::invalid_argument);
    ASSERT_THROW(diag1>>(-900), std::invalid_argument);

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

TEST (ShiftRightTest, intfTest) {
    timeD::Diagram diag1;

    diag1.addSignal('0', 5, 7);
    diag1.addSignal('1', 12, 14);
    diag1.addSignal('0', 28, 3);
    diag1.addSignal('1', 31, 2);
    diag1.addSignal('0', 33, 7);
    diag1.addSignal('X', 42, 2);

    diag1>>6;

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
    diag1>>51;

    ASSERT_EQ(diag1.getLength(), 101);
    ASSERT_EQ(diag1.getSigNum(), 5);

    ASSERT_EQ(diag1.getSigStart(4), 90);
    ASSERT_EQ(diag1.getSigLen(4), 7);

    diag1>>3;

    ASSERT_EQ(diag1.getLength(), 104);
    ASSERT_EQ(diag1.getSigNum(), 5);

    ASSERT_EQ(diag1.getSigStart(4), 93);
    ASSERT_EQ(diag1.getSigLen(4), 7);

    diag1>>5;

    ASSERT_EQ(diag1.getLength(), 109);
    ASSERT_EQ(diag1.getSigNum(), 5);

    ASSERT_EQ(diag1.getSigStart(4), 98);
    ASSERT_EQ(diag1.getSigLen(4), 7);

    if (diag1.getMaxLen() > 109) {
        diag1 >> (diag1.getMaxLen() - 109);
        ASSERT_EQ(diag1.getLength(), diag1.getMaxLen());
        ASSERT_EQ(diag1.getSigNum(), 5);

        ASSERT_EQ(diag1.getSigStart(4), 98 + diag1.getMaxLen() - 109);
        ASSERT_EQ(diag1.getSigLen(4), 7);

        diag1>>6;
        ASSERT_EQ(diag1.getSigStart(4), 104 + diag1.getMaxLen() - 109);
        ASSERT_EQ(diag1.getSigLen(4), 5);

    }
}

TEST(intfTest, shiftRightBoundary) {
    timeD::Diagram diag("010101010101010101010101111");
    ASSERT_EQ(diag.getLength(), 27);
    ASSERT_EQ(diag.getSigNum(), 24);
    ASSERT_EQ(diag.getScale(), 3);

    if (diag.getMaxLen() > 27) {
        diag >> (diag.getMaxLen() - 27);
        ASSERT_EQ(diag.getLength(), diag.getMaxLen());
        ASSERT_EQ(diag.getSigNum(), 24);

        ASSERT_EQ(diag.getSigStart(23), diag.getMaxLen() - 4);
        ASSERT_EQ(diag.getSigLen(23), 4);

        diag>>6;
        ASSERT_EQ(diag.getSigStart(20), diag.getMaxLen() - 1);
        ASSERT_EQ(diag.getSig(20), 0);
        ASSERT_EQ(diag.getSigLen(20), 1);

        diag>>2;
        ASSERT_EQ(diag.getSigStart(18), diag.getMaxLen() - 1);
        ASSERT_EQ(diag.getSig(18), 0);
        ASSERT_EQ(diag.getSigLen(18), 1);

        ASSERT_EQ(diag.getScale(), 2);

        diag>>19;
        ASSERT_EQ(diag.getSigNum(), 0);

        diag>>10;
        ASSERT_EQ(diag.getLength(), diag.getMaxLen());
        ASSERT_EQ(diag.getSigNum(), 0);
        ASSERT_EQ(diag.getScale(), 1);

    }
}


TEST (intfTest, ShiftLeft) {
    timeD::Diagram diag1;

    diag1.addSignal('0', 5, 7);
    diag1.addSignal('1', 12, 14);
    diag1.addSignal('0', 28, 3);
    diag1.addSignal('1', 31, 2);
    diag1.addSignal('0', 33, 7);
    diag1.addSignal('X', 42, 2);

    diag1<<3;

    ASSERT_EQ(diag1.getLength(), 41);
    ASSERT_EQ(diag1.getSigNum(), 5);

    ASSERT_EQ(diag1.getSig(0), 0);
    ASSERT_EQ(diag1.getSigStart(0), 2);
    ASSERT_EQ(diag1.getSigLen(0), 7);

    diag1<<4;

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
    diag1<<6;

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

    diag1<<14;

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

    diag1<<140;
    ASSERT_EQ(diag1.getLength(), 0);
    ASSERT_EQ(diag1.getSigNum(), 0);

    diag1>>140;

    ASSERT_EQ(diag1.getLength(), 140);
    ASSERT_EQ(diag1.getSigNum(), 0);
}

TEST(intfTest, shiftLefttBoundary) {
    timeD::Diagram diag("010101010101010101010101111");
    ASSERT_EQ(diag.getLength(), 27);
    ASSERT_EQ(diag.getSigNum(), 24);
    ASSERT_EQ(diag.getScale(), 3);

    diag<<5;
    ASSERT_EQ(diag.getLength(), 22);
    ASSERT_EQ(diag.getSigNum(), 19);
    ASSERT_EQ(diag.getScale(), 2);

    diag<<10;
    ASSERT_EQ(diag.getLength(), 12);
    ASSERT_EQ(diag.getSigNum(), 9);
    ASSERT_EQ(diag.getScale(), 1);

    diag<<5;
    ASSERT_EQ(diag.getLength(), 7);
    ASSERT_EQ(diag.getSigNum(), 4);
    ASSERT_EQ(diag.getScale(), 1);

    diag<<7;
    ASSERT_EQ(diag.getLength(), 0);
    ASSERT_EQ(diag.getSigNum(), 0);
    ASSERT_EQ(diag.getScale(), 1);

    diag<<7;
    ASSERT_EQ(diag.getLength(), 0);
    ASSERT_EQ(diag.getSigNum(), 0);
    ASSERT_EQ(diag.getScale(), 1);

}

TEST (intfTest, replaceTest) {
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
    ASSERT_EQ(diag1.getScale(), 1);
    ASSERT_EQ(diag1.getLength(), 19);
    ASSERT_EQ(diag1.getSigNum(), 2);

    ASSERT_EQ(diag1.getSig(0), 0);
    ASSERT_EQ(diag1.getSigStart(0), 5);
    ASSERT_EQ(diag1.getSigLen(0), 7);

    ASSERT_EQ(diag1.getSig(1), 1);
    ASSERT_EQ(diag1.getSigStart(1), 12);
    ASSERT_EQ(diag1.getSigLen(1), 7);

    diag2.replace(17, diag3);
    ASSERT_EQ(diag2.getScale(), 1);
    ASSERT_EQ(diag2.getLength(), diag2.getMaxLen());
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
    ASSERT_EQ(diag2.getSigLen(3), diag2.getMaxLen() - 17);

    diag2.replace(4, diag1);
    ASSERT_EQ(diag1.getScale(), 1);
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

TEST (intfTest, replaceTestDecScale) {
    timeD::Diagram diag1("111111111111111111110101010101010101010");
    timeD::Diagram diag2("11111111111111111111111");

    diag1.replace(15, diag2);
    ASSERT_EQ(diag1.getScale(), 1);
    ASSERT_EQ(diag1.getSigNum(), 1);
    ASSERT_EQ(diag1.getLength(), 23);

    ASSERT_EQ(diag1.getSig(0), 1);
    ASSERT_EQ(diag1.getSigStart(0), 0);
    ASSERT_EQ(diag1.getSigLen(0), 23);
}

TEST (intfTest, replaceTestIncScale) {
    timeD::Diagram diag1("10101010101010101010111111111111111111111110");
    timeD::Diagram diag2("11111111111111111111111");

    timeD::signal checker[] = {{1, 0, 3}, {0, 3, 1}, {1, 4, 1}, {0, 5, 1}, {1, 6, 1}, {0, 7, 1}, {1, 8, 1},
                               {0, 9, 1}, {1, 10, 1}, {0, 11, 1}, {1, 12, 1}, {0, 13, 1}, {1, 14, 1}, {0, 15, 1},
                               {1, 16, 1}, {0, 17, 1}, {1, 18, 1}, {0, 19, 1}, {1, 20, 23}, {0, 43, 1}};

    diag2.replace(3, diag1);
    ASSERT_EQ(diag2.getScale(), 2);
    ASSERT_EQ(diag2.getSigNum(), 20);
    ASSERT_EQ(diag2.getLength(), 44);

    for (int i = 0; i < 20; ++i) {
        //std:: cout << i <<" - " << diag2.getSig(i) << " - " << checker[i].val << std::endl;
        ASSERT_EQ(diag2.getSig(i), checker[i].val);
        ASSERT_EQ(diag2.getSigStart(i), checker[i].start);
        ASSERT_EQ(diag2.getSigLen(i), checker[i].length);
    }

}

/*
TEST (intfTest, Segment) {
    timeD::Diagram diag1;
    timeD::Diagram diag2;

    diag1.addSignal('0', 5, 7);
    diag1.addSignal('1', 12, 10);
    diag1.addSignal('0', 28, 3);
    diag1.addSignal('1', 31, 2);
    diag1.addSignal('0', 33, 2);
    diag1.addSignal('X', 42, 2);
    diag1.addSignal('1', 45, 2);
    diag1.addSignal('X', 50, 2);

    ASSERT_THROW(diag1(48, 53, diag2), std::invalid_argument);
    ASSERT_THROW(diag1(28, 28, diag2), std::invalid_argument);
    ASSERT_THROW(diag1(29, 28, diag2), std::invalid_argument);

    diag1(51, 52, diag2);
    ASSERT_EQ(diag2.getLength(), 1);
    ASSERT_EQ(diag2.getSigNum(), 0);

    diag1(28, 29, diag2);
    ASSERT_EQ(diag2.getLength(), 1);
    ASSERT_EQ(diag2.getSigNum(), 1);
    ASSERT_EQ(diag2.getSig(0), 0);
    ASSERT_EQ(diag2.getSigStart(0), 0);
    ASSERT_EQ(diag2.getSigLen(0), 1);

    diag1(6, 33, diag2);
    ASSERT_EQ(diag2.getLength(), 27);
    ASSERT_EQ(diag2.getSigNum(), 4);

    ASSERT_EQ(diag2.getSig(0), 0);
    ASSERT_EQ(diag2.getSigStart(0), 0);
    ASSERT_EQ(diag2.getSigLen(0), 6);

    ASSERT_EQ(diag2.getSig(1), 1);
    ASSERT_EQ(diag2.getSigStart(1), 6);
    ASSERT_EQ(diag2.getSigLen(1), 10);

    ASSERT_EQ(diag2.getSig(2), 0);
    ASSERT_EQ(diag2.getSigStart(2), 22);
    ASSERT_EQ(diag2.getSigLen(2), 3);

    ASSERT_EQ(diag2.getSig(3), 1);
    ASSERT_EQ(diag2.getSigStart(3), 25);
    ASSERT_EQ(diag2.getSigLen(3), 2);

    diag1(6, 37, diag2);
    ASSERT_EQ(diag2.getLength(), 31);
    ASSERT_EQ(diag2.getSigNum(), 5);

    ASSERT_EQ(diag2.getSig(0), 0);
    ASSERT_EQ(diag2.getSigStart(0), 0);
    ASSERT_EQ(diag2.getSigLen(0), 6);

    ASSERT_EQ(diag2.getSig(1), 1);
    ASSERT_EQ(diag2.getSigStart(1), 6);
    ASSERT_EQ(diag2.getSigLen(1), 10);

    ASSERT_EQ(diag2.getSig(2), 0);
    ASSERT_EQ(diag2.getSigStart(2), 22);
    ASSERT_EQ(diag2.getSigLen(2), 3);

    ASSERT_EQ(diag2.getSig(3), 1);
    ASSERT_EQ(diag2.getSigStart(3), 25);
    ASSERT_EQ(diag2.getSigLen(3), 2);

    ASSERT_EQ(diag2.getSig(4), 0);
    ASSERT_EQ(diag2.getSigStart(4), 27);
    ASSERT_EQ(diag2.getSigLen(4), 2);

    diag1(6, 34, diag2);
    ASSERT_EQ(diag2.getLength(), 28);
    ASSERT_EQ(diag2.getSigNum(), 5);

    ASSERT_EQ(diag2.getSig(0), 0);
    ASSERT_EQ(diag2.getSigStart(0), 0);
    ASSERT_EQ(diag2.getSigLen(0), 6);

    ASSERT_EQ(diag2.getSig(1), 1);
    ASSERT_EQ(diag2.getSigStart(1), 6);
    ASSERT_EQ(diag2.getSigLen(1), 10);

    ASSERT_EQ(diag2.getSig(2), 0);
    ASSERT_EQ(diag2.getSigStart(2), 22);
    ASSERT_EQ(diag2.getSigLen(2), 3);

    ASSERT_EQ(diag2.getSig(3), 1);
    ASSERT_EQ(diag2.getSigStart(3), 25);
    ASSERT_EQ(diag2.getSigLen(3), 2);

    ASSERT_EQ(diag2.getSig(4), 0);
    ASSERT_EQ(diag2.getSigStart(4), 27);
    ASSERT_EQ(diag2.getSigLen(4), 1);

    diag1(36, 40, diag2);
    ASSERT_EQ(diag2.getLength(), 4);
    ASSERT_EQ(diag2.getSigNum(), 0);

    diag1(48, 52, diag2);
    ASSERT_EQ(diag2.getLength(), 4);
    ASSERT_EQ(diag2.getSigNum(), 0);

    diag1(6, 37, diag1);
    ASSERT_EQ(diag1.getLength(), 31);
    ASSERT_EQ(diag1.getSigNum(), 5);

    ASSERT_EQ(diag1.getSig(0), 0);
    ASSERT_EQ(diag1.getSigStart(0), 0);
    ASSERT_EQ(diag1.getSigLen(0), 6);

    ASSERT_EQ(diag1.getSig(1), 1);
    ASSERT_EQ(diag1.getSigStart(1), 6);
    ASSERT_EQ(diag1.getSigLen(1), 10);

    ASSERT_EQ(diag1.getSig(2), 0);
    ASSERT_EQ(diag1.getSigStart(2), 22);
    ASSERT_EQ(diag1.getSigLen(2), 3);

    ASSERT_EQ(diag1.getSig(3), 1);
    ASSERT_EQ(diag1.getSigStart(3), 25);
    ASSERT_EQ(diag1.getSigLen(3), 2);

    ASSERT_EQ(diag1.getSig(4), 0);
    ASSERT_EQ(diag1.getSigStart(4), 27);
    ASSERT_EQ(diag1.getSigLen(4), 2);

}*/

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}