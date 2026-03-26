#pragma once

#include "SessionData.hpp"
#include "../questions/DifficultyModel.hpp"
#include "../questions/QuestionGen.hpp"

#include <vector>
#include <iostream>

class SessionManager{
    private:
        SessionConfig session_config;
        SessionState session_state;
        SessionResult session_result;
        D_model difficulty_model;
        std::vector<Question> question_array;
        
        inline const char* to_string(SessionType type);

    public:
        SessionManager(SessionType type = SessionType::ENDURANCE, int lives = 3, double rating){ // for endurance
            session_config.type = type;
            session_config.lives = lives;

            session_state.livesRemaining = session_config.lives;
            difficulty_model.set_rating(rating);
        }

        SessionManager(SessionType type, int question_count, double rating){ // for sprint and adaptive
            session_config.type = type;
            session_config.questionCount = question_count;

            difficulty_model.set_rating(rating);
        }

        SessionManager(SessionType type = SessionType::PRECISION, int question_count, int tpq, double rating){  // for precision
            session_config.type = type;
            session_config.questionCount = question_count;
            session_config.timePerQuestion = tpq;

            difficulty_model.set_rating(rating);
        }

        bool generate_batch();
        
};