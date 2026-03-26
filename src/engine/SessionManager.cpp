#include "../../include/engine/SessionManager.hpp"

bool SessionManager::generate_batch(){
    if(session_config.type == SessionType::SPRINT || session_config.type == SessionType::PRECISION){
        difficulty_model.compute();
        DifficultyParams D_parammeters = difficulty_model.getPrams();
        
        QGen Q_generator(D_parammeters);
        for(int i = 0; i< session_config.questionCount; i++){
            Q_generator.generateQuestion();
            this->question_array.push_back(Q_generator.getQuestion());
        }
        return true; // after all the question is generated
    }
    else{
        std::cout << "[Error] session_config.type: " << this->to_string(session_config.type) << ", Cannnot generate the batch" << std::endl;
        return false;  
    }
}

inline const char* SessionManager::to_string(SessionType type){
    switch(type){
        case SessionType::ADAPTIVE: return "Adaptive";
        case SessionType::ENDURANCE: return "Endurance";
        case SessionType::PRECISION: return "Precision";
        case SessionType::SPRINT: return "Sprint";
        default: return "Unknown Session Type";
    }
}