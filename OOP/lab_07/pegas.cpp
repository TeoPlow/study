#include "knight.hpp"
#include "pegas.hpp"
#include "squirrel.hpp"
#include <algorithm>

Pegas::Pegas(const int& _x, const int& _y) {
    x = _x;
    y = _y;
    alive = true;
}

void Pegas::print(std::ostream& out) {
    out << *this;
}

void Pegas::accept(NPC* attacker) {
    alive = !attacker->attack(*this);
}

bool Pegas::attack(Knight& defender) {
    bool win = false;
    // if (this->is_alive() && defender.is_alive()) {
    //     if (is_close(defender)) {
    //         int ATK = std::rand() % 6;
    //         int DEF = std::rand() % 6;
    //         win = ATK > DEF;
    //     }
    // }
    // notify(&defender, win);
    return win;

}

std::ostream& operator<<(std::ostream& out, const Pegas& other) {
    return out << "Pegas " << " {" << other.x << ", " << other.y << '}';
}

bool Pegas::is_close(const NPC& other) const noexcept {
    auto [_x, _y] = other.get_coordinates();
    return (x - _x) * (x - _x)
        + (y - _y) * (y - _y) 
        <= 10 * 10;
}

char Pegas::token() const noexcept { return alive ? 'P' : '@'; }

void Pegas::rand_move(const int& max_x, const int& max_y) {
    int step_x = std::rand() % 40 - 30;
    int step_y = std::rand() % 40 - 30;

    x = std::abs(x + step_x) % max_x;
    y = std::abs(y + step_y) % max_y;
}

