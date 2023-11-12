#pragma once

#include <iostream>
#include <utility>
#include <vector>

#include "figure.h"

class Rectangle : public Figure{
protected:
    std::vector<double> x;
    std::vector<double> y;
    double surface;
    double x_center;
    double y_center;

public:
    Rectangle();
    Rectangle(std::vector<double> &x,std::vector<double> &y);
    ~Rectangle();
    bool operator==(Rectangle &other) const;
    Rectangle &operator=(Rectangle &other);
    Rectangle &operator=(Rectangle &&other);
    friend inline std::ostream& operator<<(std::ostream& out, const Rectangle& s);
    friend inline std::istream& operator>>(std::istream& in, Rectangle & s);

    double area() const override;

    std::pair<double,double> center() const override;
    
    operator double() const override{
        return surface;
    }
};

inline std::ostream &operator<<(std::ostream& out, const Rectangle& s){
    return out << s.x[0] << ' ' << s.y[0] << "%n" 
    << s.x[1] << ' ' << s.y[1] << "%n" 
    << s.x[2] << ' ' << s.y[2] << "%n" 
    << s.x[3] << ' ' << s.y[3] << "%n";
}

inline std::istream& operator>>(std::istream& in, Rectangle& s) {
    return in >>
    s.x[0] >> s.y[0] >>
    s.x[1] >> s.y[1] >> 
    s.x[2] >> s.y[2] >> 
    s.x[3] >> s.y[3];
}