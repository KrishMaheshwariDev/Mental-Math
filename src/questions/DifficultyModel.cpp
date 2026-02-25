#include "../include/questions/DifficultyModel.hpp"

D_model::D_model(double rating){
    normalizedRating = (rating - 300)/2700;

    // getting actual operations wight based on normalized rating
    parameters.digitCount = 1 + floor(normalizedRating * 4);
    parameters.addWeight = 1 - normalizedRating;
    parameters.subWeight = 0.8 - 0.5*normalizedRating;
    parameters.mulWeight = normalizedRating;
    parameters.divWeight = std::max(0.0, normalizedRating - 0.4);

    // probability of the operations normalized from 0 to 1
    double totalWeight = 
        parameters.addWeight
        + parameters.subWeight
        + parameters.mulWeight
        + parameters.divWeight;
    
    parameters.addWeight = parameters.addWeight/totalWeight;
    parameters.subWeight = parameters.subWeight/totalWeight;
    parameters.mulWeight = parameters.mulWeight/totalWeight;
    parameters.mulWeight = parameters.divWeight/totalWeight;
    
    // Carry probability
    parameters.CarryProb = normalizedRating;

    // division allowed?
    if(normalizedRating > 0.4){
        parameters.allowDivision = true;
    }
    else{
        parameters.allowDivision = false;
    }

    //multi-step allowed?
    if(normalizedRating > 0.75){
        parameters.allowMultiStep = true;
    }
    else{
        parameters.allowMultiStep = false;
    }
}

DifficultyParams D_model::getPrams(){
    return parameters;
}
