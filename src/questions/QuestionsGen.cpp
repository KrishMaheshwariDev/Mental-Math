#include "../../include/questions/QuestionGen.hpp"

void QGen::generateQuestion() {
  // get operator
  question.operation = getOperator();

  // generating whole question
  switch (question.operation) {
  case (Operation::ADD):
    additionGen();
    break;
  case (Operation::SUBTRACT):
    subtractionGen();
    break;
  case (Operation::MULTIPLY):
    multiplicationGen();
    break;
  case (Operation::DIVIDE):
    divisionGen();
    break;
  default:
    exit(-1);
  }

  // generate the difficulty score and rating, so if the user answers are correct then
  // the user rating can be increased based on overall results 
  computeDifficultyScore();
  computeRating();
}

Question QGen::getQuestion() const { return question; }

// private methods

Operation QGen::getOperator() {
  double weights[4] = {this->parameters.addWeight, this->parameters.subWeight,
                       this->parameters.mulWeight, this->parameters.divWeight};

  std::discrete_distribution dist(weights, weights + 4);

  return (Operation)dist(gen);
}

int QGen::generateNum(int low, int high) {

  std::uniform_int_distribution dist(low, high);

  return dist(gen);
}

bool QGen::shouldCarry() {
  double carryWeights[2] = {1 - parameters.CarryProb, parameters.CarryProb};

  std::discrete_distribution dist(carryWeights, carryWeights + 2);

  return (bool)dist(gen);
}

void QGen::additionGen() {
  bool isCarry = shouldCarry();

  int d_count1 = parameters.digitCount1;
  int d_count2 = parameters.digitCount2;

  std::vector<int> operand1(d_count1);
  std::vector<int> operand2(d_count2);

  if (isCarry) {
    int chain_length = generateNum(1, parameters.CarryPropagation);
    int start_column = generateNum(0, d_count2 - 1);
    chain_length = std::min(chain_length, d_count2 - start_column);
    int end_column = start_column + chain_length;

    for (int i = 0; i < start_column; i++) {
      operand1[i] = generateNum(1, 9);
      operand2[i] = generateNum(0, 9 - operand1[i]);
    }
    // carry enforcement
    int j = start_column;
    int prevCarry = 0;
    while (chain_length != 0) {
      operand1[j] = generateNum(1, 9);
      operand2[j] = generateNum(1, 9);

      if (operand1[j] + operand2[j] + prevCarry >= 10) {
        chain_length--;
        j++;
      }
      if (operand1[j] + operand2[j] >= 10) {
        prevCarry = 1;
      }
    }
    // generating remaining columns
    for (int i = end_column; i < d_count2; i++) {
      operand1[i] = generateNum(1, 9);
      operand2[i] = generateNum(0, 9 - operand1[i]);
    }
    if (d_count1 != d_count2) {
      for (int i = d_count2; i < operand1.size(); i++) {
        operand1[i] = generateNum(1, 9);
      }
    }
  } else {
    for (int i = 0; i < operand2.size(); i++) {
      operand1[i] = generateNum(1, 9);
      operand2[i] = generateNum(1, 9 - operand1[i]);
    }

    if (d_count1 != d_count2) {
      for (int i = d_count2; i < operand1.size(); i++) {
        operand1[i] = generateNum(1, 9);
      }
    }
  }

  // setting the numbers in question object
  int num1 = 0;
  int num2 = 0;
  for (int i = operand1.size() - 1; i >= 0; i--) {
    num1 = num1 * 10 + operand1[i];
  }
  for (int i = operand2.size() - 1; i >= 0; i--) {
    num2 = num2 * 10 + operand2[i];
  }

  question.operandA = num1;
  question.operandB = num2;
  question.correctAnswer = num1 + num2;
}

void QGen::subtractionGen() {
  bool isborrow = shouldCarry();

  int d_count1 = parameters.digitCount1;
  int d_count2 = parameters.digitCount2;

  std::vector<int> operand1(d_count1);
  std::vector<int> operand2(d_count2);

  if (isborrow) {
    int chainLen = parameters.CarryPropagation;
    int startCol = generateNum(0, d_count2 - 1);
    chainLen = std::min(chainLen, d_count2 - startCol);
    int endCol = startCol + chainLen;

    for (int i = 0; i < startCol; i++) {
      operand1[i] = generateNum(1, 9);
      operand2[i] = generateNum(1, operand1[i]);
    }
    // borrow enforcement
    int j = startCol;
    int prevBorrow = 0;
    while (chainLen != 0) {
      if (prevBorrow == 0) {
        operand1[j] = generateNum(1, 9);
        operand2[j] = generateNum(operand1[j] + 1, 9);
      } else {
        operand1[j] = generateNum(1, 9);
        operand2[j] = generateNum(operand1[j], 9);
      }

      if (operand1[j] - operand2[j] - prevBorrow < 0) {
        chainLen--;
        j++;
      }
      if (j > startCol && operand1[j - 1] - operand2[j - 1] < 0) {
        prevBorrow = 1;
      } else {
        prevBorrow = 0;
      }
    }
    // generating remaining columns
    for (int i = endCol; i < d_count2; i++) {
      operand1[i] = generateNum(1, 9);
      operand2[i] = generateNum(1, operand1[i]);
    }
    if (d_count1 != d_count2) {
      for (int i = d_count2; i < operand1.size(); i++) {
        operand1[i] = generateNum(1, 9);
      }
    }
  } else {
    for (int i = 0; i < d_count2; i++) {
      operand1[i] = generateNum(1, 9);
      operand2[i] = generateNum(1, operand1[i]);
    }
    if (d_count1 != d_count2) {
      for (int i = d_count2; i < d_count1; i++) {
        operand1[i] = generateNum(1, 9);
      }
    }
  }

  int num1 = 0;
  int num2 = 0;
  for (int i = operand1.size() - 1; i >= 0; i--) {
    num1 = num1 * 10 + operand1[i];
  }
  for (int i = operand2.size() - 1; i >= 0; i--) {
    num2 = num2 * 10 + operand2[i];
  }
  if (num1 < num2) {
    std::swap(num1, num2);
  }
  question.operandA = num1;
  question.operandB = num2;
  question.correctAnswer = num1 - num2;
}

void QGen::multiplicationGen() {
  bool isCarry = shouldCarry();

  int d_count1 = parameters.digitCount1;
  int d_count2 = std::max(1, d_count1 - generateNum(0, 2));

  std::vector<int> operand1(d_count1);
  std::vector<int> operand2(d_count2);

  if(isCarry){
    int chainLen = generateNum(1, parameters.CarryPropagation);
    int startCol = generateNum(0, d_count2 - 1);
    chainLen = std::min(chainLen, d_count2 - startCol);
    int endCol = startCol + chainLen;

    for(int i = 0; i < startCol; i++){
      operand1[i] = generateNum(1, 4);
      operand2[i] = generateNum(1, 2);
    }
    // carry enforcement
    int j = startCol;
    int prevCarry = 0;
    int attempts = 0;
    while(chainLen != 0 && attempts < 100){
      if(prevCarry == 0){
        operand1[j] = generateNum(2, 9);
        operand2[j] = generateNum(5, 9);
      }else{
        operand1[j] = generateNum(5, 9);
        operand2[j] = generateNum(2, 9);
      }

      if(operand1[j] * operand2[j] + prevCarry >= 10){
        chainLen--;
        j++;
      }
      if (j > startCol && operand1[j - 1] * operand2[j - 1] + prevCarry >= 10){
        prevCarry = 1;
      }else{
        prevCarry = 0;
      }
      attempts++;
    }
    // generating remaining columns
    for(int i = endCol; i < d_count2; i++){
      operand1[i] = generateNum(1, 4);
      operand2[i] = generateNum(1, 2);
    }
    if(d_count1 != d_count2){
      for(int i = d_count2; i < operand1.size(); i++){
        operand1[i] = generateNum(1, 4);
      }
    }
  }
  else{
    for(int i = 0; i < d_count1; i++){
      operand1[i] = generateNum(1, 4);
    }
    for(int i = 0; i < d_count2; i++){
      operand2[i] = generateNum(1, 2);
    }
  }

  int num1 = 0;
  int num2 = 0;
  for (int i = operand1.size() - 1; i >= 0; i--) {
    num1 = num1 * 10 + operand1[i];
  }
  for (int i = operand2.size() - 1; i >= 0; i--) {
    num2 = num2 * 10 + operand2[i];
  }

  question.operandA = num1;
  question.operandB = num2;
  question.correctAnswer = num1 * num2;
} 

void QGen::divisionGen(){
  int d_divisor = std::max(1, generateNum(1, parameters.digitCount1 - 1));
  int d_quotient = parameters.digitCount1 - d_divisor;

  int dividend = 0;
  std::vector<int> divisor(d_divisor);
  std::vector<int> quotient(d_quotient);

  // generateing quotient, MSB (1, 9) and rest (0, 9)
  quotient[0] = generateNum(1, 9);
  for(int i = 1; i < d_quotient; i++){
    quotient[i] = generateNum(0, 9);
  }

  // generateing divisor, MSB (1, 9) and rest (0, 9)
  divisor[0] = generateNum(1, 9);
  for(int i = 1; i < d_divisor; i++){
    divisor[i] = generateNum(0, 9);
  }
  
  int numquotient = 0;
  int numdivisor = 0;
  for(int i = quotient.size() - 1; i >= 0; i--){
    numquotient = numquotient * 10 + quotient[i];
  }
  for(int i = divisor.size() - 1; i >= 0; i--){
    numdivisor = numdivisor * 10 + divisor[i];
  }
  // generateing dividend
  dividend =  numquotient * numdivisor;

  question.operandA = dividend;
  question.operandB = numdivisor;
  question.correctAnswer = numquotient;
} 

void QGen::computeDifficultyScore(){
  std::map<Operation, double> operationWieght;
  operationWieght[Operation::ADD] = 1.0;
  operationWieght[Operation::SUBTRACT] = 1.2;
  operationWieght[Operation::MULTIPLY] = 1.8;
  operationWieght[Operation::DIVIDE] = 2.2;
  
  int Digits1 = (question.operandA == 0) ? 1 : static_cast<int>(log10(question.operandB)) + 1;
  int Digits2 = (question.operandB == 0) ? 1 : static_cast<int>(log10(question.operandB)) + 1;


  double difficultyScore = (Digits1 + Digits2) * operationWieght[question.operation];
  question.difficultyScore = difficultyScore;
} 

void QGen::computeRating(){
  double rating = 300 + question.difficultyScore * 100;
  question.rating = std::clamp(rating, 300.0, 3000.0);
} 
// non class funtions and utils