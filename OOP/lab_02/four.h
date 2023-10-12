#pragma once

#include <vector>
#include <string>
#include <iostream>

class Four {
    unsigned char *array;
    size_t _size;
    void resize(size_t);
public:
    Four();
    Four(const size_t &, unsigned char);
    Four(const std::initializer_list<unsigned char> &);
    Four(const std::string &);
    Four(const Four&);
    Four(Four&&) noexcept;
    virtual ~Four() noexcept;

    size_t size() const noexcept;
    std::string to_string() const noexcept;
    int64_t to_decimal() const noexcept;

    Four operator+(const Four &);
    Four operator-(const Four &);
    Four operator=(const Four &);
    Four operator=(const std::string &);
    bool operator<(const Four &);
    bool operator>(const Four &);
    bool operator==(const Four &);
    bool operator!=(const Four &);
    bool operator<=(const Four &);
    bool operator>=(const Four &);

    friend std::ostream& operator<<(std::ostream&, const Four&);
    friend std::istream& operator>>(std::istream&, Four&);
};