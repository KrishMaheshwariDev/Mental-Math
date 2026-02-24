#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include "Questions.hpp"

// D_model take rating as input and returns a DifficultyParams struct
class D_model{
    private:
        double userRating;
        DifficultyParams parameters;
        double normalizedRating;

    public:
        D_model(double rating);
        DifficultyParams getPrams();
};