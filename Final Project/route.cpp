#include "route.h"

Route::Route(std::string source, std::string dest, double weight): source_(source), dest_(dest){
    weight_ = weight;
}

std::string Route::getSource(){
    return source_;
}

std::string Route::getDest(){
    return dest_;
}

double Route::getWeight(){
    return weight_;
}

