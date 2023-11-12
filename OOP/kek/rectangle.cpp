#include "rectangle.h"
#include <exception>
#include <cmath>

Rectangle::Rectangle(){
    x = {0.0,0.0,0.0,0.0};
    y = {0.0,0.0,0.0,0.0};
    x_center = 0.0;
    y_center = 0.0;
    surface = 0;
}

Rectangle::Rectangle(std::vector<double> &x,std::vector<double> &y) {
    this->x = x;
    this->y = y;
}

Rectangle::~Rectangle(){
    x = {};
    y = {};
    x_center = 0.0;
    y_center = 0.0;
    surface = 0;
}

bool Rectangle::operator==(Rectangle &other) const {
    if(surface == other.surface){
        return true;
    }
    else {
        return false;
    }
}

Rectangle &Rectangle::operator=(Rectangle &other) {
    x = other.x;
    y = other.y;
    x_center=other.x_center;
    y_center=other.y_center;
    surface=other.surface;
    return *this;
}
Rectangle &Rectangle::operator=(Rectangle &&other) {
    x = std::move(other.x);
    y = std::move(other.y);
    x_center = std::move(other.x_center);
    y_center = std::move(other.y_center);
    surface = std::move(other.surface);
    return *this;
}

std::pair<double,double> Rectangle::center() const {
    double x_center = double(x[0] + x[1] + x[2] + x[3]) / 4;
    double y_center = double(y[0] + y[1] + y[2] + y[3]) / 4;

    return {x_center, y_center};
}

double Rectangle::area() const {
    double surface = abs(sqrt(pow((x[1] - x[0]), 2)
    + pow((y[1] - y[0]), 2)) 
    * sqrt(pow((x[2] - x[0]), 2) 
    + pow((y[2] - y[0]), 2)));

    return surface;
}