#include <nlohmann/json.hpp>
#include "profile/profileRepo.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

bool ProfileRepo::load(Profile& user){
    if(exists()){
        std::ifstream file(filePath);
        json data = json::parse(file);

        // setting the data from json to user object
        user.setCalibrated(data["calibrated"]);
        user.setBaselineDifficulty(data["baselineDifficulty"]);
        user.setTotalSessions(data["totalSessions"]);
        user.setRating(data["rating"]);
        user.setBestAccuracy(data["bestAccuracy"]);
        user.setBestSpeed(data["bestSpeed"]);
        user.setLastSessionAccuracy(data["lastSessionAccuracy"]);
        user.setLastSessionSpeed(data["lastSessionSpeed"]);

        fileVersion = data["version"];

        return true;
    }
    else{
        std::cout << "File not found or file doesn't exists: unable to load data" << std::endl;
        return false;
    }
}

bool ProfileRepo::exists() const{
    if(std::filesystem::exists(filePath)){
        return true;
    }
    
    return false;
}

bool ProfileRepo::save(const Profile& user){
    if(exists()){
        std::ifstream file(filePath);
        json data = json::parse(file);

        // updating the data
        data["version"] = (int)data["version"] + 1;

        data["calibrated"] = user.isCalibrated();
        data["baselineDifficulty"] = user.getBaselineDifficulty();
        data["totalSessions"] = user.getTotalSessions();
        data["rating"] = user.getRating();
        data["bestAccuracy"] = user.getBestAccuracy();
        data["bestSpeed"] = user.getBestSpeed();
        data["lastSessionAccuracy"] = user.getLastSessionAccuracy();
        data["lastSessionSpeed"] = user.getLastSessionSpeed();

        // overwriting the json file
        std::ofstream jsonFile(filePath);
        jsonFile << std::setw(4) << data << std::endl;

        return true;
    }
    else{
        std::cout << "File not found or file doesn't exists: unable to save data" << std::endl;
        return false;
    }
}