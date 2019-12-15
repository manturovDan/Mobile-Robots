#include <gtest/gtest.h>
#include <iostream>

#include "../robots/Environment_describer.h"
#include "../robots/robot.h"
#include "../robots/Power_Generator.h"
#include "../robots/Sensor.h"

TEST (ConstrTest, simpleTest) {
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

TEST(originTest, RobotConst) {
    robo::Environment_describer env;
    env.setWidth(50);
    env.setHeight(50);

    std::vector<robo::Module *> modl;
    modl.push_back(new robo::Power_Generator(5, 12));
    modl.push_back(new robo::Power_Generator(5, 12));
    modl.push_back(new robo::Power_Generator(5, 12));
    modl.push_back(new robo::Sensor(3, 0, 0, 20, 4));
    robo::coordinates origin0 {0, 0};
    robo::coordinates origin1 {0, 1};
    robo::coordinates noorigin {0, 10};
    std::string desc = "Obs1";

    ASSERT_THROW(env.setObject(robo::Observation_Center_t, 5, 10, 50, modl, desc, origin0), std::invalid_argument);
    ASSERT_THROW(env.setObject(robo::Observation_Center_t, 5, 10, 50, modl, desc, origin1), std::invalid_argument);
    ASSERT_NO_THROW(env.setObject(robo::Observation_Center_t, 5, 10, 50, modl, desc, noorigin));
}

TEST (modileEnergyTest, RobotConst) {
    robo::Environment_describer env;
    env.setWidth(50);
    env.setHeight(50);

    std::vector<robo::Module *> modl;
    modl.push_back(new robo::Power_Generator(1, 12));
    modl.push_back(new robo::Power_Generator(2, 12));
    modl.push_back(new robo::Power_Generator(3, 12));
    modl.push_back(new robo::Sensor(3, 0, 0, 20, 4));
    modl.push_back(new robo::Sensor(4, 2, 0, 20, 5));

    robo::coordinates pos {5, 5};
    std::string desc = "Obs1";
    ASSERT_NO_THROW(env.setObject(robo::Observation_Center_t, 5, 10, 50, modl, desc, pos));

    for(robo::Env_Consistent_Iter it = env.begin(); it != env.end(); ++it) {
        ASSERT_EQ((*it)->getPosition(), pos);
        std::string res = "Object : Observation_Center: {5, 5}\n"
                          "Desc: 'Obs1';\n"
                          "Consumption: 10;\n"
                          "Cost: 50;\n"
                          "PortsCount: 5;\n"
                          "Appeared: 1;\n"
                          "Owner = none\n"
                          "Modules:\n"
                          "\tSensor radius = 4 direction = 2 powerConsumption = 20 priority = 5 active = 1\n"
                          "\tSensor radius = 3 direction = 0 powerConsumption = 20 priority = 4 active = 0\n"
                          "\tPower Generator energyProduction = 12 priority = 3 active = 1\n"
                          "\tPower Generator energyProduction = 12 priority = 2 active = 1\n"
                          "\tPower Generator energyProduction = 12 priority = 1 active = 1\n\n";

        ASSERT_EQ((*it)->whoami(), res);
        break;
    }
}

TEST (CommanderModuleTest, RobotConst) {
    robo::Environment_describer env;
    env.setWidth(50);
    env.setHeight(50);

    std::vector<robo::Module *> modl;
    modl.push_back(new robo::Power_Generator(1, 12));
    modl.push_back(new robo::Power_Generator(2, 12));
    modl.push_back(new robo::Power_Generator(3, 12));
    modl.push_back(new robo::Sensor(3, 0, 0, 20, 4));
    modl.push_back(new robo::Managing(4, 20, 3, 5));

    robo::coordinates pos {5, 5};
    std::string desc = "Obs1";
    ASSERT_THROW(env.setObject(robo::Command_Center_t, 5, 10, 50, modl, desc, pos), std::invalid_argument);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}