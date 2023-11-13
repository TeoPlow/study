#include <cmath>

#include "trapeze.h"

Trapeze::Trapeze() {
    x = {0.0,0.0,0.0,0.0};
    y = {0.0,0.0,0.0,0.0};
    x_center = 0.0;
    y_center = 0.0;
    surface = 0;
}

Trapeze::Trapeze(std::vector<double> &x,std::vector<double> &y) {
    this->x = x;
    this->y = y;
}

Trapeze::~Trapeze() {
    x = {};
    y = {};
    x_center = 0.0;
    y_center = 0.0;
    surface = 0;
}

bool Trapeze::operator==(Trapeze &other) const {
    if(surface == other.surface){
        return true;
    }
    else {
        return false;
    }
}

Trapeze &Trapeze::operator=(Trapeze &other){
    x = other.x;
    y = other.y;
    x_center = other.x_center;
    y_center = other.y_center;
    surface = other.surface;
    return *this;
}
Trapeze &Trapeze::operator=(Trapeze &&other){
    x = std::move(other.x);
    y = std::move(other.y);
    x_center = std::move(other.x_center);
    y_center = std::move(other.y_center);
    surface = std::move(other.surface);
    return *this;
}

std::pair<double,double> Trapeze::center() const {
    double x_center = double(x[0] + x[1] + x[2] + x[3]) / 4;
    double y_center = double(y[0] + y[1] + y[2] + y[3]) / 4;

    return {x_center, y_center};
}

double Trapeze::area() const {
    double surface = abs(0.5 * (x[0] * 
    (y[1] - y[2]) + x[1] * (y[2] - y[0]) + 
    x[2] * (y[0] - y[1])));

    return surface;
}