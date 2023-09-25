#include <twelve.h>

Twelve::Twelve() : array(0, 0) {}
Twelve::Twelve(const size_t & n, unsigned char t = 0) {
    array.resize(n, t);
}
Twelve::Twelve(const std::initializer_list<unsigned char> &t) {
    array = t;
    std::reverse(array.begin(), array.end()); 
}
Twelve::Twelve(const std::string &t) {
    for (int i = t.size() - 1; i > 0; --i) {
        array.push_back(t[i]);
    }
}
Twelve::Twelve(const Twelve& other) {
    array = other.array;
}
Twelve::Twelve(Twelve&& other) noexcept {
    array = other.array; // cringe
}
virtual Twelve::~Twelve() noexcept : default;

Twelve Twelve::operator+(Twelve &other);
Twelve Twelve::operator-(Twelve &other);
Twelve Twelve::operator=(Twelve &other);
bool Twelve::operator<(Twelve &other);
bool Twelve::operator>(Twelve &other);
bool Twelve::operator==(Twelve &other);
bool Twelve::operator<=(Twelve &other);
bool Twelve::operator>=(Twelve &other);
