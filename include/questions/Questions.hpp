#pragma once

struct Question{
    int operandA;
    int operandB;
    Operation operation;
    float correctAnswer;
    double difficultyScore;
    double rating;
};

enum class Operation {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
    // MIXED,
    // MULTISTEP
};