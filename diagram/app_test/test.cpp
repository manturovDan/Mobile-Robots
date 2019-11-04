#include <cstdio>

#include <gtest/gtest.h>

#include "../src/diagram.h"
#include "../src/diagfile.h"

TEST (fileTest, txtTest) {
    std::ostream nullstream(0);
    std::ostream& emp = nullstream;

    timeD::Diagram diag1 = "0000111010010100101010011101000001XXX110";
    timeD::Diagram diag2;

    std::string filename = "txtTest.txt";
    fileD::writeTextDiag(filename, diag1, emp);

    fileD::readTextDiag(filename, diag2, emp);

    ASSERT_EQ(diag1.getLength(), diag2.getLength());
    ASSERT_EQ(diag1.getSigNum(), diag2.getSigNum());
    ASSERT_EQ(diag1.getScale(), diag2.getScale());

    for (int i = 0; i < diag1.getSigNum(); ++i) {
        ASSERT_EQ(diag1.getSig(i), diag2.getSig(i));
        ASSERT_EQ(diag1.getSigStart(i), diag2.getSigStart(i));
        ASSERT_EQ(diag1.getSigLen(i), diag2.getSigLen(i));
    }

    remove(&filename[0]);
}

TEST (fileTest, binTest) {
    std::ostream nullstream(0);
    std::ostream& emp = nullstream;

    timeD::Diagram diag1 = "0000111010010100101010011101000001XXX110";
    timeD::Diagram diag2;

    std::string filename = "txtTest";
    fileD::writeBinary(filename, diag1, emp);

    fileD::readBinary(filename, diag2, emp);

    ASSERT_EQ(diag1.getLength(), diag2.getLength());
    ASSERT_EQ(diag1.getSigNum(), diag2.getSigNum());
    ASSERT_EQ(diag1.getScale(), diag2.getScale());

    for (int i = 0; i < diag1.getSigNum(); ++i) {
        ASSERT_EQ(diag1.getSig(i), diag2.getSig(i));
        ASSERT_EQ(diag1.getSigStart(i), diag2.getSigStart(i));
        ASSERT_EQ(diag1.getSigLen(i), diag2.getSigLen(i));
    }

    remove(&filename[0]);
}

TEST (fileTest, xmlTest) {
    std::ostream nullstream(0);
    std::ostream& emp = nullstream;

    timeD::Diagram diag1 = "0000111010010100101010011101000001XXX110";
    timeD::Diagram diag2;

    std::string filename = "txtTest.xml";
    fileD::writeXML(filename, diag1, emp);

    fileD::readXML(filename, diag2, emp);

    ASSERT_EQ(diag1.getLength(), diag2.getLength());
    ASSERT_EQ(diag1.getSigNum(), diag2.getSigNum());
    ASSERT_EQ(diag1.getScale(), diag2.getScale());

    for (int i = 0; i < diag1.getSigNum(); ++i) {
        ASSERT_EQ(diag1.getSig(i), diag2.getSig(i));
        ASSERT_EQ(diag1.getSigStart(i), diag2.getSigStart(i));
        ASSERT_EQ(diag1.getSigLen(i), diag2.getSigLen(i));
    }

    remove(&filename[0]);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}