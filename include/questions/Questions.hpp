#pragma once
#include <random>
#include <vector>

enum class Operation {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
    // MIXED,
    // MULTISTEP
};

struct Question{
    int operandA;
    int operandB;
    Operation operation;
    float correctAnswer;
    double difficultyScore;
    double rating;
};

struct DifficultyParams{
    int digitCount;
    double addWeight;
    double subWeight;
    double mulWeight;
    double divWeight;
    double CarryProb;
    bool allowDivision;
    bool allowMultiStep;
    // double complexityLevel;
};
