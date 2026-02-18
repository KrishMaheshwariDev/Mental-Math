#pragma once

class Profile{
    private:
        bool calibrated;
        double baselineDifficulty;
        int totalSessions;
        double rating;
        double bestAccuracy;
        double bestSpeed;
        double lastSessionAccuracy;
        double lastSessionSpeed;

    public:
        Profile(){};

        // getter methods
        bool isCalibrated() const;
        double getBaselineDifficulty() const;
        int getTotalSessions() const;
        double getRating() const;
        double getBestAccuracy() const;
        double getBestSpeed() const;
        double getLastSessionAccuracy() const;
        double getLastSessionSpeed() const;

        // setter methods
        void setCalibrated(bool input);
        void setBaselineDifficulty(double input);
        void setTotalSessions(int input);
        void setRating(double input);
        void setBestAccuracy(double input);
        void setBestSpeed(double input);
        void setLastSessionAccuracy(double input);
        void setLastSessionSpeed(double input);

        // utils
        void increamentTotalSession();
};