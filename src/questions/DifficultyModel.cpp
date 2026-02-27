#include "../include/questions/DifficultyModel.hpp"

void D_model::compute(){
    // main scalar component to comute difficulty model
    double scalar = 1 - pow(std::numbers::e, -userRating / k);

    // digit Count
    int stage = std::min(5, int(6 * scalar));
    switch (stage)
    {
    case 0:
        parameters.digitCount1 = 1;
        parameters.digitCount2 = 1;
        break;
    case 1:
        parameters.digitCount1 = 2;
        parameters.digitCount2 = 1;
        break;
    case 2:
        parameters.digitCount1 = 3;
        parameters.digitCount2 = 1;
        break;
    case 3:
        parameters.digitCount1 = 2;
        parameters.digitCount2 = 2;
        break;  
    case 4:
        parameters.digitCount1 = 3;
        parameters.digitCount2 = 2;
        break; 
    case 5:
        parameters.digitCount1 = 3;
        parameters.digitCount2 = 3;
        break; 
    default:
        break;
    }

    // Operator probabilities
    double A = pow(1 - scalar, 1.2);
    double M = pow(scalar, 1.3);

    parameters.addWeight = 0.4 * A + 0.05;
    parameters.subWeight = 0.3 * A + 0.05;
    parameters.mulWeight = 0.45 * M + 0.05;
    parameters.divWeight = 0.25 * M + 0.05;

    double totalWeight = parameters.addWeight + parameters.subWeight + parameters.mulWeight + parameters.divWeight;

    parameters.addWeight /= totalWeight;
    parameters.subWeight /= totalWeight; 
    parameters.mulWeight /= totalWeight; 
    parameters.divWeight /= totalWeight; 

    // Carry probability
    parameters.CarryProb = 0.05 + 0.75 * pow(scalar, 1.1);
    if (scalar < 0.6) parameters.CarryPropagation = 1;
    else parameters.CarryPropagation = 2;

    //complexity level
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-0.04, 0.04);

    parameters.complexityLevel = pow(scalar, 1.3) + dis(gen);
}

DifficultyParams D_model::getPrams() const{
    return parameters;
}
