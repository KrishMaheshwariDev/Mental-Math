#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <random>
#include "Questions.hpp"

// D_model take rating as input and returns a DifficultyParams struct
class D_model{
    private:
        double k = 900;
        double userRating;
        DifficultyParams parameters;

    public:
        D_model(double rating): userRating(rating){};
        void compute();
        DifficultyParams getPrams() const;
};