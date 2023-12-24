#include "knight.hpp"
#include "pegas.hpp"
#include "squirrel.hpp"
#include <algorithm>

Squirrel::Squirrel(const int& _x, const int& _y, const std::string& _name) {
    x = _x;
    y = _y;
    name = _name;
    alive = true;
}

void Squirrel::print(std::ostream& out) {
    out << *this;
}

void Squirrel::accept(NPC* attacker, const int& distance) {
    if (alive && dynamic_cast<Pegas*>(attacker)) {
        bool win = is_close(*attacker, distance);
        if (win) 
            alive = false;
        notify(attacker, win);
    }
}

std::ostream& operator<<(std::ostream& out, const Squirrel& other) {
    return out << "Squirrel " << other.name << " {" << other.x << ", " << other.y << '}';
}
