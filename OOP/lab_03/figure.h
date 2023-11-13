#pragma once

#include <iostream>

class Figure{
    protected:
        Figure() = default;

    public:
        virtual ~Figure() = default;
        virtual std::pair<double,double> center() const = 0;
        virtual double area() const = 0;
        virtual explicit operator double() const = 0;
};