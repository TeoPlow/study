#pragma once

#include <iostream>
#include <vector>

#include "figure.h"

template <typename T>
class Trapeze : public Figure<T>{
    protected:
        std::vector<T> x;
        std::vector<T> y;
        T surface;
        T x_center;
        T y_center;

    public:
        Trapeze() {
            x = {0.0,0.0,0.0,0.0};
            y = {0.0,0.0,0.0,0.0};
            x_center = 0.0;
            y_center = 0.0;
            surface = 0;
        }

        Trapeze(std::vector<T> &x,std::vector<T> &y) {
            this->x = x;
            this->y = y;
        }

        ~Trapeze() {
            x = {};
            y = {};
            x_center = 0.0;
            y_center = 0.0;
            surface = 0;
        }

        bool operator==(Trapeze<T> &other) const {
            if(surface == other.surface){
                return true;
            }
            else {
                return false;
            }
        }

        Trapeze &operator=(Trapeze<T>  &other){
            x = other.x;
            y = other.y;
            x_center = other.x_center;
            y_center = other.y_center;
            surface = other.surface;
            return *this;
        }
        Trapeze &operator=(Trapeze<T>  &&other){
            x = std::move(other.x);
            y = std::move(other.y);
            x_center = std::move(other.x_center);
            y_center = std::move(other.y_center);
            surface = std::move(other.surface);
            return *this;
        }

        std::pair<T,T> center() const {
            T x_center = T(x[0] + x[1] + x[2] + x[3]) / 4;
            T y_center = T(y[0] + y[1] + y[2] + y[3]) / 4;

            return {x_center, y_center};
        }

        T area() const {
            T surface = abs(0.5 * (x[0] * 
            (y[1] - y[2]) + x[1] * (y[2] - y[0]) + 
            x[2] * (y[0] - y[1])));

            return surface;
        }

        friend inline std::ostream& operator<<(std::ostream& out, const Trapeze<T> &s);
        friend inline std::istream& operator>>(std::istream& in, Trapeze<T>  &s) {
            return in >>
            s.x[0] >> s.y[0] >>
            s.x[1] >> s.y[1] >> 
            s.x[2] >> s.y[2] >> 
            s.x[3] >> s.y[3];
        }

        operator T() const override{
            return surface;
        }
};

template <typename T>
inline std::ostream &operator<<(std::ostream& out, const Trapeze<T> &s){
    return out << s.x[0] << ' ' << s.y[0] << "%n" 
    << s.x[1] << ' ' << s.y[1] << "%n" 
    << s.x[2] << ' ' << s.y[2] << "%n" 
    << s.x[3] << ' ' << s.y[3] << "%n";
}