#include "../include/questions/DifficultyModel.hpp"

void D_model::compute(){
    // main scalar component to comute difficulty model
    double scalar = 1 - pow(std::numeric_limits<double>::epsilon(), userRating / k);

    // digit Count
    parameters.digitCount1 = 1 + floor(3 * pow(scalar, 0.8));
    parameters.digitCount2 = 1 + floor(2 * pow(scalar, 0.9));

    // Operator probabilities
    double A = pow(1 - scalar, 2);
    double M = scalar * scalar;

    parameters.addWeight = 0.45 * A;
    parameters.subWeight = 0.35 * A;
    parameters.mulWeight = 0.45 * M;
    parameters.divWeight = 0.25 * M;

    double totalWeight = parameters.addWeight + parameters.subWeight + parameters.mulWeight + parameters.divWeight;

    parameters.addWeight /= totalWeight;
    parameters.subWeight /= totalWeight; 
    parameters.mulWeight /= totalWeight; 
    parameters.divWeight /= totalWeight; 

    // Carry probability
    parameters.CarryProb = 0.1 + 0.75 * pow(scalar, 1.2);
    parameters.CarryPropagation = 1 + floor(2 * pow(scalar, 1.5));

    //complexity level
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-0.05, 0.05);

    parameters.complexityLevel = pow(scalar, 1.3) + dis(gen);
}

DifficultyParams D_model::getPrams() const{
    return parameters;
}
