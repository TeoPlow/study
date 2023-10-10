#pragma once

#include <vector>
#include <string>
#include <iostream>

class Four
{
public:
 Four();
 Four(const size_t & n, unsigned char t = 0);
 Four(const std::initializer_list< unsigned char> &t);
 Four(const string &t);
 Four(const Four& other);
 Four(Four&& other) noexcept;
 virtual ~Four() noexcept;
};