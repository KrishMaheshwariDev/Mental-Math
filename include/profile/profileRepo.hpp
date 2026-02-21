#pragma once
// #include <filesystem>
#include "profile.hpp"
#include <filesystem>

class ProfileRepo{
    private:
        std::filesystem::path filePath;
        int fileVersion;
    public:
        ProfileRepo(): filePath("../data/profile.json"){}

        bool load(Profile& profile);
        bool exists() const;
        bool save(const Profile& profile);
};