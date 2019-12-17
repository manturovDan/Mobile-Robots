#include <gtest/gtest.h>
#include <iostream>

#include "../robots/Environment_describer.h"
#include "../robots/robot.h"
#include "../robots/Power_Generator.h"
#include "../robots/Sensor.h"
#include "../robots/interface.h"
#include "../robots/Ai_Deep.h"

//lee
//count of researched points
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

TEST (EnvSetObj, Env) {
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
    ASSERT_THROW(env.setObject(robo::Command_Center_t, 5, 10, 50, modl, desc), std::invalid_argument);
    ASSERT_THROW(env.setObject(robo::Obstacle_t, 5, 10, 50, modl, desc, pos4), std::invalid_argument);
    ASSERT_NO_THROW(env.setObject(robo::Interest_t, pos4));
    ASSERT_THROW(env.setObject(robo::Robot_Scout_t, 5, 10, 50, modl, desc, pos5), std::invalid_argument);
    ASSERT_NO_THROW(env.setObject(robo::Robot_Commander_t, 5, 10, 50, modl, desc));
    ASSERT_THROW(env.setObject(robo::Command_Center_t, 5, 10, 50, modl, desc), std::invalid_argument);
    ASSERT_THROW(env.setObject(robo::Obstacle_t, 5, 10, 50, modl, desc), std::invalid_argument);
}

TEST (XMLload, XMLTest) {
    robo::Environment_describer env;
    std::string filename = "../tests/mapXMLtest.xml";
    interf::EnvXMLCreate(filename, env);
    auto ai = robo::Ai_Deep(&env);
    robo::Managing::setAI(&ai);

    robo::Env_Consistent_Iter it = env.begin();
    robo::coordinates pos1 {5 ,1};
    ASSERT_EQ((*it)->getPosition(), pos1);
    ASSERT_STREQ(typeid(**it).name(), "N4robo8ObstacleE");

    ++it;
    robo::coordinates pos2 {1 ,2};
    ASSERT_EQ((*it)->getPosition(), pos2);
    ASSERT_STREQ(typeid(**it).name(), "N4robo8ObstacleE");

    ++it;
    robo::coordinates pos3 {15, 20};
    ASSERT_EQ((*it)->getPosition(), pos3);
    ASSERT_STREQ(typeid(**it).name(), "N4robo8ObstacleE");

    ++it;
    robo::coordinates pos4 {0, 22};
    ASSERT_EQ((*it)->getPosition(), pos4);
    ASSERT_STREQ(typeid(**it).name(), "N4robo14Interest_PointE");

    ++it;
    robo::coordinates pos5 {10, 14};
    ASSERT_EQ((*it)->getPosition(), pos5);
    ASSERT_STREQ(typeid(**it).name(), "N4robo14Interest_PointE");

    ++it;
    robo::coordinates pos6 {29, 24};
    ASSERT_EQ((*it)->getPosition(), pos6);
    ASSERT_STREQ(typeid(**it).name(), "N4robo14Command_CenterE");
    robo::Command_Center * com1;
    com1 = dynamic_cast<robo::Command_Center *>(*it);
    ASSERT_NE(com1, nullptr);
    ASSERT_EQ(com1->getPosition(), pos6);
    std::string s1 = com1->getDescription();
    std::string gen = "general";
    ASSERT_EQ(s1 , gen);

    ++it;
    robo::coordinates pos7 {8, 4};
    ASSERT_EQ((*it)->getPosition(), pos7);
    ASSERT_STREQ(typeid(**it).name(), "N4robo18Observation_CenterE");
    robo::Observation_Center * sub1;
    sub1 = dynamic_cast<robo::Observation_Center *>(*it);
    ASSERT_NE(sub1, nullptr);
    ASSERT_EQ(sub1->getPosition(), pos7);
    std::string ss1 = sub1->getDescription();
    std::string sub1s = "subord1";
    ASSERT_EQ(ss1 , sub1s);
    ASSERT_EQ(sub1->getMaxRadius(), 8);

    ++it;
    robo::coordinates pos8 {0, 2}; //default
    ASSERT_EQ((*it)->getPosition(), pos8);
    ASSERT_STREQ(typeid(**it).name(), "N4robo11Robot_ScoutE");
    robo::Robot_Scout * sc1;
    sc1 = dynamic_cast<robo::Robot_Scout *>(*it);
    ASSERT_NE(sc1, nullptr);
    std::string sc1d = sc1->getDescription();
    std::string sc1dr = "subord_move";
    ASSERT_EQ(sc1d , sc1dr);
    ASSERT_EQ(sc1->getMaxRadius(), 8);
    ASSERT_EQ(sc1->getBlocked(), true);

    ++it;
    robo::coordinates pos9 {0, 2}; //default
    ASSERT_EQ((*it)->getPosition(), pos9);
    ASSERT_STREQ(typeid(**it).name(), "N4robo15Robot_CommanderE");
    robo::Robot_Commander * rcom;
    rcom = dynamic_cast<robo::Robot_Commander *>(*it);
    ASSERT_NE(rcom, nullptr);
    std::string cdesc = rcom->getDescription();
    std::string cn1r = "general_move";
    ASSERT_EQ(cdesc, cn1r);
    ASSERT_EQ(rcom->getMaxRadius(), 9);

    ASSERT_EQ(rcom->getPair(), sc1);
    ASSERT_EQ(sc1->getOwner(), rcom);

    ASSERT_EQ(sub1->getOwner(), nullptr);

    ++it;
    ASSERT_EQ(it, env.end());

}

TEST(AiStaticRes, AiTest) {
    robo::Environment_describer env;
    std::string filename = "../tests/mapXMLtest.xml";
    interf::EnvXMLCreate(filename, env);
    auto ai = robo::Ai_Deep(&env);
    robo::Managing::setAI(&ai);

    robo::Env_Consistent_Iter it = env.begin();
    robo::coordinates obs1 {5 ,1};

    ++it;
    robo::coordinates obs2 {1 ,2};

    ++it;
    robo::coordinates obs3 {15, 20};

    ++it;
    robo::coordinates int1 {0, 22};

    ++it;
    robo::coordinates int2 {10, 14};

    ++it;
    robo::coordinates general_pos {29, 24};
    robo::Command_Center * general;
    general = dynamic_cast<robo::Command_Center *>(*it);

    ++it;
    robo::coordinates subord1_pos {8, 4};
    robo::Observation_Center * subord1;
    subord1 = dynamic_cast<robo::Observation_Center *>(*it);

    ++it;
    robo::Robot_Scout * subord_move;
    subord_move = dynamic_cast<robo::Robot_Scout *>(*it);

    ++it;
    robo::Robot_Commander * general_move;
    general_move = dynamic_cast<robo::Robot_Commander *>(*it);

    ++it;
    ASSERT_EQ(it, env.end());


    ai.run();
    ASSERT_EQ(ai.countOfOpened(), 4);

    auto map_it = ai.begin();

    for (unsigned int x = 28; x <= 29; ++x) {
        for (unsigned y = 23; y <= 24; ++y) {
            robo::coordinates curCor {x, y};
            ASSERT_EQ(map_it->first, curCor);
            if (x == 29 && y == 24) {
                ASSERT_EQ(map_it->second.iam, general);
            }
            else {
                ASSERT_EQ(map_it->second.iam, nullptr);
            }
            map_it++;
        }
    }
}

TEST (ResearchSimple, MapRes) {
    robo::Environment_describer env;
    std::string filename = "../tests/mapXMLtest.xml";
    interf::EnvXMLCreate(filename, env);
    auto ai = robo::Ai_Deep(&env);
    robo::Managing::setAI(&ai);

    robo::Env_Consistent_Iter it = env.begin();
    robo::coordinates obs1 {5 ,1};

    ++it;
    robo::coordinates obs2 {1 ,2};

    ++it;
    robo::coordinates obs3 {15, 20};

    ++it;
    robo::coordinates int1 {0, 22};

    ++it;
    robo::coordinates int2 {10, 14};

    ++it;
    robo::coordinates general_pos {29, 24};
    robo::Command_Center * general;
    general = dynamic_cast<robo::Command_Center *>(*it);

    ++it;
    robo::coordinates subord1_pos {8, 4};
    robo::Observation_Center * subord1;
    subord1 = dynamic_cast<robo::Observation_Center *>(*it);

    ++it;
    robo::Robot_Scout * subord_move;
    subord_move = dynamic_cast<robo::Robot_Scout *>(*it);

    ++it;
    robo::Robot_Commander * general_move;
    general_move = dynamic_cast<robo::Robot_Commander *>(*it);

    ++it;
    ASSERT_EQ(it, env.end());


    ai.run();
    ASSERT_EQ(ai.countOfOpened(), 4);

    ASSERT_EQ(env.getTime(), 0);
    unsigned int time = 0;
    while (true) {
        env.plusTime();
        ASSERT_EQ(env.getTime(), ++time);

        if (ai.getEnd()) {
            break;
        }

        ai.nextComp();
        if(ai.getMd()->makeSteps(env.getTime()))
            ai.setEnd();
    }
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}