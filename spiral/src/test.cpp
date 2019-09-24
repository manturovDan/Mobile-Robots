#include <gtest/gtest.h>

#include "aspiral.h"

TEST (spiralClass, justConstrAndGetter) {
	aspiral::Spiral spir;
	ASSERT_EQ(1, spir.getStep());
	aspiral::Spiral spir2(5.1);
	ASSERT_DOUBLE_EQ(5.1, spir2.getStep());
	ASSERT_ANY_THROW(aspiral::Spiral spir3(-5.11110101));
}

TEST (spiralClass, setter) {
	aspiral::Spiral spir;
	spir.setStep(8.9123);
	ASSERT_DOUBLE_EQ(8.9123, spir.getStep());
	ASSERT_ANY_THROW(spir.setStep(-1));
	spir.setStep(0);
	ASSERT_EQ(0, spir.getStep());
}

TEST (spiralParams, distToCenter) {
	aspiral::Spiral spir;
	ASSERT_EQ(1, spir.centerDist(2 * M_PI));
	ASSERT_EQ(1, spir.centerDist(-2 * M_PI));
	ASSERT_NEAR(2.44760, spir.centerDist(2.81 + 4*M_PI), 0.001);
	ASSERT_NEAR(2.44760, spir.centerDist(-(2.81 + 4*M_PI)), 0.001);

	spir.setStep(8.9123);
	ASSERT_NEAR(sqrt(pow(15.36, 2) + pow(17.78, 2)), spir.centerDist(4 + 4*M_PI), 0.01);

	ASSERT_NEAR((8.9123 * (4 + 4*M_PI) / (2 * M_PI)), spir.centerDist(4 + 4*M_PI), 0.00001);

	spir.setStep(0);
	ASSERT_NEAR(0, spir.centerDist(2.81 + 100*M_PI), 0.001);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}