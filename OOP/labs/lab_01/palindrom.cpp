#include <iostream>
#include <algorithm> 
#include "palindrom.h"

int palindrom(std::string s) {
    std::string s_new = s;
    reverse(s_new.begin(), s_new.end());

    return (s == s_new);
}