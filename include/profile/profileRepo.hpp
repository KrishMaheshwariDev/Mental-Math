#pragma once
// #include <filesystem>
#include "profile.hpp"

class ProfileRepo{
    private:
        std::string filePath;
    
    public:
        ProfileRepo(): filePath("../../data/profile.json"){}

        bool load(Profile& profile);
        bool exists() const;
        bool save(const Profile& profile);
};