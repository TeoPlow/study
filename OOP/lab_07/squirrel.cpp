#include "knight.hpp"
#include "pegas.hpp"
#include "squirrel.hpp"
#include <algorithm>

Squirrel::Squirrel(const int& _x, const int& _y) {
    x = _x;
    y = _y;
    alive = true;
}

void Squirrel::print(std::ostream& out) {
    out << *this;
}

void Squirrel::accept(NPC* attacker) {
    alive = !attacker->attack(*this);
}

bool Squirrel::attack(Knight& defender) {
    bool win = false;
    if (this->is_alive() && defender.is_alive()) {
        if (is_close(defender)) {
            int ATK = std::rand() % 6;
            int DEF = std::rand() % 6;
            win = ATK > DEF;
        }
    }
    notify(&defender, win);
    return win;
}

std::ostream& operator<<(std::ostream& out, const Squirrel& other) {
    return out << "Squirrel " << " {" << other.x << ", " << other.y << '}';
}

bool Squirrel::is_close(const NPC& other) const noexcept {
    auto [_x, _y] = other.get_coordinates();
    return (x - _x) * (x - _x)
        + (y - _y) * (y - _y) 
        <= 5 * 5;
}

char Squirrel::token() const noexcept { return alive ? 'S' : '@'; }

void Squirrel::rand_move(const int& max_x, const int& max_y) {
    int step_x = std::rand() % 10 - 5;
    int step_y = std::rand() % 10 - 5;

    x = std::abs(x + step_x) % max_x;
    y = std::abs(y + step_y) % max_y;
}
