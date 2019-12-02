#include "Ai_Deep.h"
#include "Environment_describer.h"

namespace robo {
    Ai_Deep::Ai_Deep(Environment_describer * env) {
        for (Env_Consistent_Iter env_iter = env->begin(); env_iter != env->end(); ++env_iter) {
            if(!strcmp(typeid(**env_iter).name(), "N4robo18Observation_CenterE")) {
                std::cout << "Observ" << std::endl;
                //stopped here
            } else if(!strcmp(typeid(**env_iter).name(), "N4robo14Command_CenterE")) {
                std::cout << "Comc" << std::endl;
            }
        }
    }
}