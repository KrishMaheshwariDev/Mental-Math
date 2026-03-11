#include "../include/questions/QuestionGen.hpp"

void QGen::generateQuestion(){
    // get operator
    question.operation = getOperator();

    // generating whole question
    switch(question.operation){
        case(Operation::ADD):
            additionGen();
            break;
        case(Operation::SUBTRACT):
            subtractionGen();
            break;
        case(Operation::MULTIPLY):
            multiplicationGen();
            break;
        case(Operation::DIVIDE):
            divisionGen();
            break;
        default:
            exit(-1); 
    }
}

Question QGen::getQuestion() const{
    return question;
}

// private methods

Operation QGen::getOperator(){
    std::array<double,4> weights = {
        parameters.addWeight,
        parameters.subWeight,
        parameters.mulWeight,
        parameters.divWeight
    };

    std::discrete_distribution<> dist(weights.begin(), weights.end());

    return (Operation)dist(gen);
}

int QGen::generateNum(int low, int high){
    
    std::uniform_int_distribution<> dist(low, high);

    return dist(gen);
}

bool QGen::shouldCarry(){
    std::array<double, 2> carryProb = {1 - parameters.CarryProb, parameters.CarryProb};

    std::discrete_distribution<> dist(carryProb.begin(), carryProb.end());

    return (bool)dist(gen);
}

void QGen::additionGen(){
    bool isCarry = shouldCarry();

    int d_count1 = parameters.digitCount1;
    int d_count2 = parameters.digitCount2;

    std::vector<int> operand1(d_count1);
    std::vector<int> operand2(d_count2);

    if(isCarry){
        int chain_length = generateNum(1, parameters.CarryPropagation);
        int start_column = generateNum(0, d_count2-1);
        chain_length = std::min(chain_length, d_count2 - start_column);
        int end_column = start_column + chain_length;

        for(int i = 0; i < start_column; i++){
            operand1[i] = generateNum(1, 9);
            operand2[i] = generateNum(0,9 - operand1[i]);
        }
        // carry enforcement
        int j = start_column;
        int prevCarry = 0;
        while(chain_length != 0){
            operand1[j] = generateNum(1, 9);
            operand2[j] = generateNum(1, 9);

            if(operand1[j] + operand2[j] + prevCarry >= 10){
                chain_length--;
                j++;
            }
            if(operand1[j] + operand2[j] >= 10){
                prevCarry = 1;
            }
        }
        // generating remaining columns
        for(int i = end_column; i < d_count2; i++){
            operand1[i] = generateNum(1, 9);
            operand2[i] = generateNum(0,9 - operand1[i]);
        }
        if(d_count1 != d_count2){
            for(int i = d_count2; i < operand1.size(); i++){
                operand1[i] = generateNum(1, 9);
            }
        }
    }
    else{
        for(int i = 0; i < operand2.size(); i++){
            operand1[i] = generateNum(1, 9);
            operand2[i] = generateNum(1, 9 - operand1[i]);
        }

        if(d_count1 != d_count2){
            for(int i = d_count2; i < operand1.size(); i++){
                operand1[i] = generateNum(1, 9);
            }
        }   
    }

    // setting the numbers in question object
    int num1 = 0;
    int num2 = 0;
    for(int i = 0; i < operand1.size(); i++){
        num1 += pow(10, i) * operand1[i];
    }
    for(int i = 0; i< operand2.size(); i++){
        num2 += pow(10, i) * operand2[i];
    }

    question.operandA = num1;
    question.operandB = num2;
}

// non class funtions and utils
