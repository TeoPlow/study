#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

//#include "four.h"

class Four {
private:
    unsigned char *array;
    size_t _size;
    void resize(size_t);
    int res_10;
public:
    Four();
    Four(const size_t &, unsigned char);
    Four(const std::initializer_list<unsigned char> &);
    Four(const std::string &);
    Four(const Four&);
    Four(Four&&) noexcept;
    ~Four() noexcept;

    size_t size() const noexcept;
    std::string to_string() const noexcept;
    int to_10() const noexcept;

    Four operator+(const Four &);
    Four operator-(const Four &);
    bool operator<(const Four &);
    bool operator>(const Four &);
    bool operator==(const Four &);
    
};


// ---------------------------------


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

// Return a number in 10 notation
int Four::to_10() const noexcept {
    int res_10 = 0;
    for (int i = 0; i < _size; ++i) {
        res_10 += to_int(array[i]) * std::pow(4, i);
    }
    return res_10;
}

// Summ
Four Four::operator+(const Four &other) {
    int res = this-> to_10() + other.to_10();

    std::string result;
    std::string rev_result;
    int w = res;
    char dop;

    while (w > 0){
        if (w % 4 == 10){
            result.append("3");
        }
        if ((w % 4 != 10)){
            dop = w % 4;
            result.append(std::to_string(dop));
        }
        w /= 4;
    }

    for (int q = result.length() - 1; q >= 0; q--){
        rev_result += result[q];
    }


    return Four(rev_result);
}

//Differ
Four Four::operator-(const Four &other) {
    std::string result;
    std::string rev_result;

    if (this -> to_10() < other.to_10()){
        throw std::invalid_argument("Nigative number");
    }

    if (this -> to_10() == other.to_10()){
        throw std::invalid_argument("Nigative number");
    }

    if (this -> to_10() > other.to_10()){
        int res = this -> to_10() - other.to_10();
        int w = res;
        char dop;

        while (w > 0){
            if (w % 4 == 10){
                result.append("3");
            }
            if ((w % 4 != 10)){
                dop = w % 4;
                result.append(std::to_string(dop));
            }
            w /= 4;
        }

        for (int q = result.length() - 1; q >= 0; q--){
            rev_result += result[q];
        }
    }
        return Four(rev_result);
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

//-------------------------------------------

int main() {
    Four a, b;
    char oper;
    std::cout << "Enter numbers and operator:\n";
    try {
        std::string num1,num2;
        std::cout << "Enter number 1: \n num1 = ";
        std::cin >> num1;

        std::cout << "Enter number 2: \n num2 = ";
        std::cin >> num2;

        Four a(num1);
        Four b(num2);

        std::cout << "num1 in decimal = " << a.to_10() << '\n';
        std::cout << "num2 in decimal = " << b.to_10() << '\n' << '\n';

        std::cout << "a + b = " << (a + b).to_string() << '\n';
        std::cout << "a - b = " << (a - b).to_string() << '\n';
        std::cout << "a > b: " << (a > b) << '\n';
        std::cout << "a < b: " << (a < b) << '\n';
        std::cout << "a = b: " << (a == b) << '\n' << '\n';


        std::cout << "Length a : " << a.size() << std::endl;
        std::cout << "Length b : " << b.size() << std::endl << std::endl;

        std::cout<<"String a: "<<a.to_string()<<std::endl;
        std::cout<<"String b: "<<b.to_string()<<std::endl;
    }
    catch(std::invalid_argument ex) {
        std::cout << "Invalid argument: " << ex.what() << std::endl;
    }
    catch(std::underflow_error ex) {
        std::cout << "Underflow error: " << ex.what() << std::endl;
    }
    
    return 0;
}