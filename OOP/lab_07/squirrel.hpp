#pragma once
#include "NPC.hpp"


class Squirrel: public NPC {
public:
    Squirrel(const int&, const int&);

    void print(std::ostream&) override;

    void accept(NPC*) override;
    bool attack(Knight&) override;

    friend std::ostream& operator<<(std::ostream&, const Squirrel&);

    bool is_close(const NPC&) const noexcept override;

    char token() const noexcept override;
    void rand_move(const int&, const int&) override;
};
