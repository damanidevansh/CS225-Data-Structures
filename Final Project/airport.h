#pragma once

#include <string>

class Airport {
public:
    Airport(std::string name, std::string country, std::string iata, double latitude, double longitude);
    std::string getName();
    std::string getCountry();
    std::string getIATA();
    double getLong();
    double getLat();
    bool getVisited();
    void setVisited(bool value);
private:
    //Name Country IATA Latitude Longitude
    std::string name_;
    std::string country_;
    std::string iata_;
    double lat_;
    double long_;
    bool visited_;
};

