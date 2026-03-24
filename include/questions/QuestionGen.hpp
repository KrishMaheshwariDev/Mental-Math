#pragma once
#include <random>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include "Questions.hpp"

class QGen {
private:
  DifficultyParams parameters;
  Question question;
  std::random_device rd;
  std::mt19937 gen;

  Operation getOperator();
  int generateNum(int low, int high);
  bool shouldCarry();

  void additionGen();
  void subtractionGen();
  void multiplicationGen();
  void divisionGen();

  void computeDifficultyScore();
  void computeRating();

public:
  QGen(DifficultyParams params) : parameters(params), gen(rd()) {};
  void generateQuestion();
  Question getQuestion() const;
};