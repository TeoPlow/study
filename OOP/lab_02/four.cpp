#include "four.h"
#include <cmath>
#include <cstring>

void Four::resize(size_t size) {
    unsigned char* new_array = new unsigned char[size];

    std::memcpy( new_array, array, size * sizeof(unsigned char));

    _size = size;
    delete [] array;
    array = new_array;
}

Four::Four() {
    array = new unsigned char;
    *array = '0';
    _size = 1;
}
Four::Four(const size_t & n, unsigned char t = '0') {
    if (!(t >= '0' && t <= '3'))
        throw std::invalid_argument("character isn't a Four digit");
    array = new unsigned char [n];
    _size = n;
    for (int i = 0; i < _size; ++i) {
        array[i] = t;
    }
}
Four::Four(const std::initializer_list<unsigned char> &t) {
    array = new unsigned char[t.size()];
    _size = t.size();

    int i = t.size() - 1;
    for (unsigned char elem : t) {
        if (!(elem >= '0' && elem <= '3'))
            throw std::invalid_argument("character isn't a Four digit");
        array[i--] = elem;
    }
}
Four::Four(const std::string &t) {
    array = new unsigned char[t.size()];
    _size = t.size();
    
    int i = t.size() - 1;
    for (unsigned char elem : t) {
        if (!(elem >= '0' && elem <= '3'))
            throw std::invalid_argument("character isn't a Four digit");
        array[i--] = elem;
    }
}
Four::Four(const Four& other) {
    array = new unsigned char[other._size];
    std::memcpy(array, other.array, other._size);
    _size = other._size;
}
Four::Four(Four&& other) noexcept {
    array = other.array;
    _size = other._size;
    other.array = nullptr;
    other._size = 0;
}
Four::~Four() { }

unsigned char to_char(int n) { 
    if (n < 4) {
        return n + '0';
    }
    else {
        return n - 4 + '4';
    }
}
int to_int(unsigned char c) {
    if (c >= '0' && c <= '3') {
        return c - '0';
    }
    else {
        return c - '4' + 4;
    }
}

// Number of elements
size_t Four::size() const noexcept {
    return _size;
}

// Return the value as a string
std::string Four::to_string() const noexcept {
    std::string result;
    for (int i = _size - 1; i >= 0; --i) {
        result += array[i];
    }
    return result;
}
// Return a number in decimal notation
int64_t Four::to_decimal() const noexcept {
    int64_t result = 0;
    for (int i = 0; i < _size; ++i) {
        result += to_int(array[i]) * std::pow(4, i);
    }
    return result;
}

Four Four::operator+(const Four &other) {
    const unsigned char *a, *b; // a > b
    size_t size_a, size_b;
    if (_size< other._size){
        a = other.array;
        size_a = other._size;
        b = array;
        size_b = _size;
    }
    else {
        b = other.array;
        a = array;
        size_a = _size;
        size_b = other._size;

    }
    Four result = Four(size_a, '0');

    int remain = 0;
    for (int i = 0; i < size_b; ++i) {
        int val = to_int(a[i]) + to_int(b[i]) + remain;
        result.array[i] = to_char(val % 4);
        remain = val / 4;
    }
    for (int i = size_b; i < size_a; ++i) {
        int val = to_int(a[i]) + remain;
        result.array[i] = to_char(val % 4);
        remain = val / 4;
    }
    if (remain > 0) {
        result.resize(_size + 1);
        result.array[result._size - 1] = to_char(remain);
    }

    return result;
}
Four Four::operator-(const Four &other) {
    Four result = *this;

    if (*this < other) {
        throw std::underflow_error("Four doesn't support negative values");
    }

    int remain = 0;
    for (int i = 0; i < other._size; ++i) {
        int val = to_int(array[i]) - to_int(other.array[i]) - remain;
        result.array[i] = to_char((val + 4) % 4);
        remain = val < 0 ? 1 : 0;
    }
    if (_size > other._size)
        result.array[other._size] = to_char(to_int(array[other._size]) - remain);
    
    int cnt_zero = 0;
    for (int i = result._size - 1; i > 0; --i) {
        if (result.array[i] == '0') {
            ++cnt_zero;
        }
        else {
            break;
        }
    }
    result.resize(result._size - cnt_zero);

    return result;
}
Four Four::operator=(const Four &other) {
    resize(other._size);

    for (int i = 0; i < _size; ++i) {
        array[i] = other.array[i];
    }

    return *this;
}
Four Four::operator=(const std::string &s) {
    *this = Four(s);

    return *this;
}
bool Four::operator<(const Four &other) {
    if (_size < other._size)
        return true;
    if (_size > other._size)
        return false;
    
    for (int i = _size - 1; i >= 0; --i) {
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
    if (_size > other._size)
        return true;
    if (_size < other._size)
        return false;
    
    for (int i = _size - 1; i >= 0; --i) {
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
    if (_size != other._size)
        return false;
    
    for (int i = _size - 1; i >= 0; --i) {
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