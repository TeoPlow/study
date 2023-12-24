#include "knight.hpp"
#include "pegas.hpp"
#include "squirrel.hpp"
#include <algorithm>

Pegas::Pegas(const int& _x, const int& _y, const std::string& _name) {
    x = _x;
    y = _y;
    name = _name;
    alive = true;
}

void Pegas::print(std::ostream& out) {
    out << *this;
}

void Pegas::accept(NPC* attacker, const int& distance) {
    
}

std::ostream& operator<<(std::ostream& out, const Pegas& other) {
    return out << "Pegas " << other.name << " {" << other.x << ", " << other.y << '}';
}