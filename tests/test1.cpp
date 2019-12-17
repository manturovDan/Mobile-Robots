#include <gtest/gtest.h>
#include <iostream>

#include "../robots/Environment_describer.h"
#include "../robots/robot.h"
#include "../robots/Power_Generator.h"
#include "../robots/Sensor.h"

//envoronment construction
//static ai checking
//real direction
//lee
//count of researched points
//finding grey
//creating route
//route table optimization
//blocked points
//blocked areas

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

TEST (EnvCollision, EnvConst) {
    robo::Environment_describer env;
    env.setWidth(50);
    env.setHeight(50);

    std::vector<robo::Module *> modl;
    modl.push_back(new robo::Power_Generator(1, 12));
    modl.push_back(new robo::Power_Generator(2, 12));
    modl.push_back(new robo::Power_Generator(3, 120));
    modl.push_back(new robo::Sensor(3, 0, 0, 20, 4));
    modl.push_back(new robo::Managing(4, 20, 3, 5));

    robo::coordinates pos {5, 5};
    std::string desc = "Obs1";
    ASSERT_NO_THROW(env.setObject(robo::Command_Center_t, 5, 10, 50, modl, desc, pos));
    ASSERT_THROW(env.setObject(robo::Obstacle_t, pos), std::invalid_argument);
    ASSERT_THROW(env.setWidth(5000), std::invalid_argument);
    ASSERT_THROW(env.setHeight(5), std::invalid_argument);
    ASSERT_THROW(env.setWidth(-1), std::invalid_argument);
    ASSERT_EQ(env.getWidth(), 50);
    ASSERT_EQ(env.getHeight(), 50);
}

TEST (EnvSizes, EnvConst) {
    ASSERT_THROW(robo::Environment_describer env (10, 5);, std::invalid_argument);
    ASSERT_THROW(robo::Environment_describer env (10, 5000);, std::invalid_argument);
    ASSERT_NO_THROW(robo::Environment_describer env (70, 50));
    ASSERT_THROW(robo::Environment_describer env (10, 3);, std::invalid_argument);
}

TEST (EnvResize, Env) {
    robo::Environment_describer env (70, 50);

    std::vector<robo::Module *> modl;
    modl.push_back(new robo::Power_Generator(1, 12));
    modl.push_back(new robo::Power_Generator(2, 12));
    modl.push_back(new robo::Power_Generator(3, 30));
    modl.push_back(new robo::Sensor(3, 0, 0, 20, 4));
    modl.push_back(new robo::Managing(4, 20, 3, 5));
    robo::coordinates pos1 {5, 5};
    robo::coordinates pos2 {5, 6};
    robo::coordinates pos3 {69, 40};
    robo::coordinates pos4 {5, 5};
    robo::coordinates pos5 {70, 0};
    robo::coordinates pos6 {0, 0};
    robo::coordinates pos7 {0, 1};
    std::string desc = "desc";

    ASSERT_NO_THROW(env.setObject(robo::Command_Center_t, 5, 10, 50, modl, desc, pos1));
    ASSERT_NO_THROW(env.setObject(robo::Observation_Center_t, 5, 10, 50, modl, desc, pos2));
    ASSERT_NO_THROW(env.setObject(robo::Obstacle_t, pos3));
    ASSERT_THROW(env.setObject(robo::Interest_t, pos4), std::invalid_argument);
    ASSERT_THROW(env.setObject(robo::Obstacle_t, pos5), std::invalid_argument);
    ASSERT_THROW(env.setObject(robo::Obstacle_t, pos6), std::invalid_argument);
    ASSERT_THROW(env.setObject(robo::Obstacle_t, pos7), std::invalid_argument);
    ASSERT_THROW(env.setObject(robo::Interest_t, pos6), std::invalid_argument);
    ASSERT_THROW(env.setObject(robo::Interest_t, pos7), std::invalid_argument);

    ASSERT_THROW(env.setWidth(55), std::invalid_argument);
    ASSERT_EQ(env.getHeight(), 50);
    ASSERT_EQ(env.getWidth(), 70);
    ASSERT_NO_THROW(env.setWidth(75));
    ASSERT_EQ(env.getHeight(), 50);
    ASSERT_EQ(env.getWidth(), 75);
}

//env match setObj

TEST (EnvFill, Env) {
    robo::Environment_describer env (70, 50);

    std::vector<robo::Module *> modl;
    modl.push_back(new robo::Power_Generator(1, 12));
    modl.push_back(new robo::Power_Generator(2, 12));
    modl.push_back(new robo::Power_Generator(3, 30));
    modl.push_back(new robo::Sensor(3, 0, 0, 20, 4));
    modl.push_back(new robo::Managing(4, 20, 3, 5));
    robo::coordinates pos1 {5, 5};
    robo::coordinates pos2 {5, 6};
    robo::coordinates pos3 {69, 40};
    robo::coordinates pos4 {5, 1};
    robo::coordinates pos5 {2, 0};
    std::string desc = "desc";

    ASSERT_NO_THROW(env.setObject(robo::Command_Center_t, 5, 10, 50, modl, desc, pos1));
    ASSERT_NO_THROW(env.setObject(robo::Command_Center_t, 5, 10, 50, modl, desc, pos2));
    ASSERT_NO_THROW(env.setObject(robo::Obstacle_t, pos3));
    ASSERT_NO_THROW(env.setObject(robo::Interest_t, pos4));
    ASSERT_NO_THROW(env.setObject(robo::Observation_Center_t, 5, 10, 50, modl, desc, pos5));

    robo::Env_Consistent_Iter it = env.begin();

    ASSERT_EQ((*it)->getPosition(), pos1);
    ASSERT_NO_THROW(dynamic_cast<robo::Command_Center *>(*it)->getPosition());
    ASSERT_STREQ(typeid(**it).name(), "N4robo14Command_CenterE");
    auto * com1 = dynamic_cast<robo::Command_Center *>(*it);
    ASSERT_EQ(com1->getCountPorts(), 5);
    ASSERT_EQ(com1->getEnergyConsumption(), 10);
    ASSERT_EQ(com1->getCountModules(), 5);
    ASSERT_EQ(com1->getMaxRadius(), 3);
    ASSERT_EQ(com1->isManager(), true);
    com1->chooseManModule();

    it++;
    auto * com2 = dynamic_cast<robo::Command_Center *>(*it);
    com2->chooseManModule();
    ASSERT_NE(com1->manMod(), com2->manMod());
    ASSERT_EQ(com2->getPosition(), pos2);

    it++;
    auto obs = dynamic_cast<robo::Obstacle *>(*it);
    ASSERT_EQ(obs->getPosition(), pos3);

    it++;
    auto inter = dynamic_cast<robo::Interest_Point *>(*it);
    ASSERT_EQ(inter->getPosition(), pos4);

    it++;
    auto observ = dynamic_cast<robo::Observation_Center *>(*it);
    ASSERT_EQ(observ->getPosition(), pos5);
    ASSERT_EQ(observ->getCountModules(), 5);
    ASSERT_EQ(observ->getMaxRadius(), 3);

    it++;
    ASSERT_EQ(it, env.end());

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}