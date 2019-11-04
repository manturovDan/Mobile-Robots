#include <gtest/gtest.h>

#include "../src/diagram.h"
#include "../src/diagfile.h"

TEST (fileTest, txtTest) {
    timeD::Diagram diag1 = "0000111010010100101010011101000001XXX110";
    timeD::Diagram diag2 = diag1;

    std::string filename = "txtTest.txt";
    fileD::writeTextDiag(filename, diag1);

    fileD::readTextDiag(filename, diag2);

    ASSERT_EQ(diag1.getLength(), diag2.getLength());
    ASSERT_EQ(diag1.getSigNum(), diag2.getSigNum());
    ASSERT_EQ(diag1.getScale(), diag2.getScale());

    for (int i = 0; i < diag1.getSigNum(); ++i) {
        ASSERT_EQ(diag1.getSig(i), diag2.getSig(i));
        ASSERT_EQ(diag1.getSigStart(i), diag2.getSigStart(i));
        ASSERT_EQ(diag1.getSigLen(i), diag2.getSigLen(i));
    }
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}