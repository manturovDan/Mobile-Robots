#include "Ai_Deep.h"
#include "Environment_describer.h"

namespace robo {
    Ai_Deep::Ai_Deep(Environment_describer * env) {
        for (Env_Consistent_Iter env_iter = env->begin(); env_iter != env->end(); ++env_iter) {
            if(!strcmp(typeid(**env_iter).name(), "N4robo14Command_CenterE")) {
                add_point(*env_iter);
                auto * cc = dynamic_cast<Command_Center *>(*env_iter);
                cc->subdue();
                add_point(cc);

                for (auto cit : *cc->manMod()) {
                    add_point(cit);
                }
                //cc->research();
                //cc->look(); //LOOK ALL SUBORDINATORS
            }
        }
    }

    void Ai_Deep::add_point(Map_Object *obj) {
        ai_dict.insert(std::pair<coordinates, map_point>(obj->getPosition(), {obj, false, false, false, false}));
    }

    void Ai_Deep::print(std::ostream & stream) {

    }
}