#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

class Twelve {
    std::vector<unsigned char> array;
public:
    Twelve();
    Twelve(const size_t & n, unsigned char t = 0);
    Twelve(const std::initializer_list<unsigned char> &t);
    Twelve(const std::string &t);

    Twelve(const Twelve& other);
    Twelve(Twelve&& other) noexcept;
    virtual ~Twelve() noexcept;

    Twelve operator+(Twelve &other);
    Twelve operator-(Twelve &other);
    Twelve operator=(Twelve &other);
    bool operator<(Twelve &other);
    bool operator>(Twelve &other);
    bool operator==(Twelve &other);
    bool operator<=(Twelve &other);
    bool operator>=(Twelve &other);

};