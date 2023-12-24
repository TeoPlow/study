#pragma once
#include "NPC.hpp"


class Knight: public NPC {
public:
    Knight(const int&, const int&);

    void print(std::ostream&) override;

    void accept(NPC*) override;
    bool attack(Squirrel&) override;

    friend std::ostream& operator<<(std::ostream&, const Knight&);

    bool is_close(const NPC&) const noexcept override;

    char token() const noexcept override;
    void rand_move(const int&, const int&) override;
};
