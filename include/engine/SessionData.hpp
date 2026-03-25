#pragma once

#include "../questions/QuestionGen.hpp";

enum class SessionType{
    SPRINT,
    PRECISION,
    ENDURANCE,
    ADAPTIVE
};

struct SessionConfig{
    SessionType type;
    int questionCount;  // ignored for endurance
    int timePerQuestion;    // for precision
    int lives;  // for endurance
};

struct SessionState{
    int currentIndex;
    int livesRemaining;
    int correctCount;
    bool isActive;
};

struct Attempt{
    Question question;

    int userAnswer;
    bool isCorrect;

    double timeTaken;   // seconds
    long long timestamp;
};

struct SessionResult{
    SessionType type;
    std::vector<Attempt> attempts;
};