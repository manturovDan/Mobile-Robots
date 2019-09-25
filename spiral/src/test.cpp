#include <gtest/gtest.h>

#include "aspiral.h"

TEST (spiralClass, justConstrAndGetter) {
	aspiral::Spiral spir;
	ASSERT_EQ(1, spir.getStep());
	aspiral::Spiral spir2(5.1);
	ASSERT_DOUBLE_EQ(5.1, spir2.getStep());
	ASSERT_THROW(aspiral::Spiral spir3(-5.11110101), std::invalid_argument);
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
	ASSERT_EQ(0, spir.centerDist(2.81 + 100*M_PI));
}

TEST (spiralParams, secArea) {
	aspiral::Spiral spir(0);
	ASSERT_EQ(0, spir.areaOfSector(M_PI, 2*M_PI));
	spir.setStep(3.14);
	ASSERT_EQ(0, spir.areaOfSector(2*M_PI, 2*M_PI));

	double angle = (2 - 0.15) * M_PI;
	double s1 = (angle / 2) * pow(spir.centerDist(2 * M_PI), 2);
	double s2 = (angle / 2) * pow(spir.centerDist(0.15 * M_PI), 2);
	double s3 = (angle / 2) * sqrt(pow(spir.centerDist(2 * M_PI), 2) * pow(spir.centerDist(0.15 * M_PI), 2));

	ASSERT_NEAR((s1 + s2 + s3) / 3, spir.areaOfSector(0.15*M_PI, 2*M_PI), 0.0001); //second formulae
	ASSERT_NEAR((s1 + s2 + s3) / 3, spir.areaOfSector(-0.15*M_PI, -2*M_PI), 0.0001);
	ASSERT_NEAR((s1 + s2 + s3) / 3, spir.areaOfSector(2*M_PI, 0.15*M_PI), 0.0001);
}

TEST (spiralParams, areaBefNCoil) {
	aspiral::Spiral spir(0);
	ASSERT_EQ(0, spir.areaBefCoil(100));
	spir.setStep(3.14);
	ASSERT_NEAR(spir.areaOfSector(0, 2*M_PI), spir.areaBefCoil(0), 0.00001);
	ASSERT_NEAR((125 - 64)*(M_PI * pow(spir.centerDist(5*2*M_PI), 2))/(3*25), spir.areaBefCoil(5), 0.00001);//second formulae
}

TEST (spiralParams, areaCircle) {
	aspiral::Spiral spir(0);
	ASSERT_EQ(0, spir.areaOfCircle(100));
	spir.setStep(29.171);
	ASSERT_NEAR(spir.areaBefCoil(101) - spir.areaBefCoil(100), spir.areaOfCircle(100), 0.001);
}

TEST (spiralParams, lengthCurve) {
	aspiral::Spiral spir(0);
	ASSERT_EQ(0, spir.curveLen(100));
	ASSERT_EQ(0, spir.curveLen(-100));
	spir.setStep(2);
	ASSERT_NEAR(139.524, spir.curveLen(9.4 * M_PI), 0.1); //integral (1/pi)sqrt(1 + (x)^2)dx from 0 to 9.4*pi
	ASSERT_NEAR(139.524, spir.curveLen(-9.4 * M_PI), 0.1); //integral (1/pi)sqrt(1 + (x)^2)dx from 0 to 9.4*pi
}

TEST (spiralParams, curvRadius) {
	aspiral::Spiral spir(0);
	ASSERT_EQ(0, spir.curveRad(100));
	ASSERT_EQ(0, spir.curveRad(-100));
	spir.setStep(2);
	ASSERT_NEAR(2/(4 * M_PI), spir.curveRad(0), 0.001);
	ASSERT_NEAR(2/(4 * M_PI), spir.curveRad(0), 0.001);
	ASSERT_NEAR(pow(pow(9.4 * M_PI, 2) + 1, 1.5) / (M_PI * (pow(9.4 * M_PI, 2) + 2)), spir.curveRad(9.4 * M_PI), 0.001);
	ASSERT_NEAR(pow(pow(9.4 * M_PI, 2) + 1, 1.5) / (M_PI * (pow(9.4 * M_PI, 2) + 2)), spir.curveRad(-9.4 * M_PI), 0.001);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}