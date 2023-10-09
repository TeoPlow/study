#include "four.h"
#include <cmath>

Four::Four() : array(1, '0') {}
Four::Four(const size_t & n, unsigned char t = '0') {
    if (!(t >= '0' && t <= '3'))
        throw std::invalid_argument("character isn't a Four digit");
    array.resize(n, t);
}
Four::Four(const std::initializer_list<unsigned char> &t) {
    array.resize(t.size());
    
    int i = t.size() - 1;
    for (unsigned char elem : t) {
        if (!(elem >= '0' && elem <= '3'))
            throw std::invalid_argument("character isn't a Four digit");
        array[i--] = elem;
    }
}
Four::Four(const std::string &t) {
    for (int i = t.size() - 1; i >= 0; --i) {
        if (!(t[i] >= '0' && t[i] <= '3'))
            throw std::invalid_argument("character isn't a Four digit");
        array.push_back(t[i]);
    }
}
Four::Four(const Four& other) {
    array = other.array;
}
Four::Four(Four&& other) noexcept {
    array = other.array;
}
Four::~Four() { }

unsigned char to_char(int n) {
    if (n < 4) {
        return n + '0';
    }
}
int to_int(unsigned char c) {
    if (c >= '0' && c <= '3') {
        return c - '0';
    }
}

// Number of elements
size_t Four::size() const noexcept {
    return array.size();
}
// Return the value as a string
std::string Four::to_string() const noexcept {
    std::string result;
    for (int i = array.size() - 1; i >= 0; --i) {
        result += array[i];
    }
    return result;
}
// Return a number in decimal notation
int64_t Four::to_decimal() const noexcept {
    int64_t result = 0;
    for (int i = 0; i < array.size(); ++i) {
        result += to_int(array[i]) * std::pow(4, i);
    }
    return result;
}

Four Four::operator+(const Four &other) {
    const std::vector<unsigned char> *a, *b;
    if (array.size() < other.array.size()){
        a = &other.array;
        b = &array;
    }
    else {
        a = &array;
        b = &other.array;
    }
    Four result = Four(a->size(), '0');

    int remain = 0;
    for (int i = 0; i < b->size(); ++i) {
        int val = to_int((*a)[i]) + to_int((*b)[i]) + remain;
        result.array[i] = to_char(val % 4);
        remain = val / 4;
    }
    for (int i = b->size(); i < a->size(); ++i) {
        int val = to_int((*a)[i]) + remain;
        result.array[i] = to_char(val % 4);
        remain = val / 4;
    }
    if (remain > 0) {
        result.array.push_back(to_char(remain));
    }

    return result;
}
Four Four::operator-(const Four &other) {
    Four result = *this;

    if (*this < other) {
        throw std::underflow_error("Four doesn't support negative values");
    }

    int remain = 0;
    for (int i = 0; i < other.array.size(); ++i) {
        int val = to_int(array[i]) - to_int(other.array[i]) - remain;
        result.array[i] = to_char((val % 4 + 4) % 4);
        remain = val < 0 ? 1 : 0;
    }
    if (array.size() > other.array.size())
        result.array[other.array.size()] = to_char(to_int(array[other.array.size()]) - remain);
    while(result.array[result.array.size() - 1] == '0') {
        result.array.pop_back();
    }

    return result;
}
Four Four::operator=(const Four &other) {
    array = other.array;
    return *this;
}
Four Four::operator=(const std::string &s) {
    *this = Four(s);
    return *this;
}
bool Four::operator<(const Four &other) {
    if (array.size() < other.array.size())
        return true;
    if (array.size() > other.array.size())
        return false;
    
    for (int i = array.size() - 1; i >= 0; --i) {
        if (array[i] < other.array[i]) {
            return true;
        }
        if (array[i] > other.array[i]) {
            return false;
        }
    }

    return false;
}
bool Four::operator>(const Four &other) {
    if (array.size() > other.array.size())
        return true;
    if (array.size() < other.array.size())
        return false;
    
    for (int i = array.size() - 1; i >= 0; --i) {
        if (array[i] > other.array[i]) {
            return true;
        }
        if (array[i] < other.array[i]) {
            return false;
        }
    }

    return false;
}
bool Four::operator==(const Four &other) {
    if (array.size() != other.array.size())
        return false;
    
    for (int i = array.size() - 1; i >= 0; --i) {
        if (array[i] != other.array[i]) {
            return false;
        }
    }

    return true;
}
bool Four::operator!=(const Four &other) {
    return !(*this == other);
}
bool Four::operator<=(const Four &other) {
    return !(*this > other);
}
bool Four::operator>=(const Four &other) {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& cout, const Four& num) {
    return cout << num.to_string();
}
std::istream& operator>>(std::istream& cin, Four& num) {
    std::string val;
    cin >> val;
    num = val;
    return cin;
}