#pragma once

#include <iostream>
#include <vector>

#include "figure.h"

class Trapeze : public Figure{
protected:
    std::vector<double> x;
    std::vector<double> y;
    double surface;
    double x_center;
    double y_center;

public:
    Trapeze();
    Trapeze(std::vector<double> &x,std::vector<double> &y);
    ~Trapeze();
    bool operator==(Trapeze &other) const;
    Trapeze &operator=(Trapeze &other);
    Trapeze &operator=(Trapeze &&other);
    friend inline std::ostream& operator<<(std::ostream& out, const Trapeze& s);
    friend inline std::istream& operator>>(std::istream& in, Trapeze & s);

    double area() const override;

    std::pair<double,double> center() const override;

    operator double() const override{
        return surface;
    }
};

inline std::ostream &operator<<(std::ostream& out, const Trapeze& s){
    return out << s.x[0] << ' ' << s.y[0] << "%n" 
    << s.x[1] << ' ' << s.y[1] << "%n" 
    << s.x[2] << ' ' << s.y[2] << "%n" 
    << s.x[3] << ' ' << s.y[3] << "%n";
}

inline std::istream& operator>>(std::istream& in, Trapeze& s) {
    return in >>
    s.x[0] >> s.y[0] >>
    s.x[1] >> s.y[1] >> 
    s.x[2] >> s.y[2] >> 
    s.x[3] >> s.y[3];
}