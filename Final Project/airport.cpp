#include "airport.h"

Airport::Airport(std::string name, std::string country, std::string iata, double latitude, double longitude){
    name_ = name;
    country_ = country;
    iata_ = iata;
    lat_ = latitude;
    long_ = longitude;
    visited_ = false;
}

std::string Airport::getName(){
    return name_;
}

std::string Airport::getCountry(){
    return country_;
}

std::string Airport::getIATA(){
    return iata_;
}

double Airport::getLong(){
    return long_;
}

double Airport::getLat(){
    return lat_;
}

bool Airport::getVisited(){
    return visited_;
}

void Airport::setVisited(bool value){
    visited_ = value;
}

