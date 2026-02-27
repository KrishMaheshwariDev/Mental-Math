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
    int digitCount1; // rannge of operand 1
    int digitCount2; // range of operand 2

    // operator probability
    double addWeight;
    double subWeight;
    double mulWeight;
    double divWeight;

    // carry prob and no. of times carry taken for solving
    double CarryProb;
    int CarryPropagation;

    // allow multi- steps (means multiple operators in same questions )
    // bool allowMultiStep;

    // total complexity of the model according to rating
    // with some random ness so for the same rating model must not be exact everytime
    double complexityLevel;
};
