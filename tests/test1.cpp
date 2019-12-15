#include <gtest/gtest.h>

#include "../robots/Environment_describer.h"
#include "../robots/robot.h"
#include "../robots/Power_Generator.h"

TEST (ConstrTest, ASCIItest) {
    ASSERT_EQ(1, 1);
}

//envoronment construction
//static ai checking
//real direction
//lee
//count of researched points
//finding grey
//creating route

TEST (SimpleCreating, RobotConst) {
    robo::Environment_describer env;
    env.setWidth(50);
    env.setHeight(50);

    std::vector<robo::Module *> modl;
    modl.push_back(new robo::Power_Generator(5, 12));
    modl.push_back(new robo::Power_Generator(5, 12));
    modl.push_back(new robo::Power_Generator(5, 12));
    modl.push_back(new robo::Power_Generator(5, 12));
    modl.push_back(new robo::Power_Generator(5, 12));
    modl.push_back(new robo::Power_Generator(5, 12));
    robo::coordinates pos {5, 5};
    std::string desc = "Obs1";

    ASSERT_THROW(env.setObject(robo::Observation_Center_t, 5, 10, 50, modl, desc, pos), std::invalid_argument);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}