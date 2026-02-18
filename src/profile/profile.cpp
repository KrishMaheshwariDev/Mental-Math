#include "../include/profile/profile.hpp"

// Setter methods

void Profile::setCalibrated(bool input){
    calibrated = input;
}

void Profile::setBaselineDifficulty(double input){
    baselineDifficulty = input;
}

void Profile::setTotalSessions(int input){
    totalSessions = input;
}

void Profile::setRating(double input){
    rating = input;
}

void Profile::setBestAccuracy(double input){
    bestAccuracy = input;
}

void Profile::setBestSpeed(double input){
    bestSpeed = input;
}

void Profile::setLastSessionAccuracy(double input){
    lastSessionAccuracy = input;
}

void Profile::setLastSessionSpeed(double input){
    lastSessionSpeed = input;
}

// getter methods

bool Profile::isCalibrated() const{
    return calibrated;
}

double Profile::getBaselineDifficulty() const{
    return baselineDifficulty;
}

int Profile::getTotalSessions() const{
    return totalSessions;
}

double Profile::getRating() const{
    return rating;
}

double Profile::getBestAccuracy() const{
    return bestAccuracy;
}

double Profile::getBestSpeed() const{
    return bestSpeed;
}

double Profile::getLastSessionAccuracy() const{
    return lastSessionAccuracy;
}

double Profile::getLastSessionSpeed() const{
    return lastSessionSpeed;
}

// utils

void Profile::increamentTotalSession(){
    totalSessions++;
}