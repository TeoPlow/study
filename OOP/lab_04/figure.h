#pragma once

#include <iostream>

template <class T>
class Figure{
    protected:
        Figure() = default;

    public:
        virtual ~Figure() = default;
        virtual std::pair<T, T> center() const = 0;
        virtual T area() const = 0;
        virtual explicit operator double() const = 0;
};