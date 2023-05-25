#pragma once

#include <string>

class Route {
public:
    Route(std::string source, std::string dest, double weight);
    std::string getSource();
    std::string getDest();
    double getWeight();
private:
    std::string source_;
    std::string dest_;
    double weight_;
};

