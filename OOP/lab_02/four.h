#pragma once

#include <vector>
#include <string>
#include <iostream>

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
    int to_10() noexcept;

    std::string operator+(const Four &);
    std::string operator-(const Four &);
    bool operator<(const Four &);
    bool operator>(const Four &);
    bool operator==(const Four &);

};