#include "knight.hpp"
#include "pegas.hpp"
#include "squirrel.hpp"
#include <algorithm>

Knight::Knight(const int& _x, const int& _y, const std::string& _name) {
    x = _x;
    y = _y;
    name = _name;
    alive = true;
}

void Knight::print(std::ostream& out) {
    out << *this;
}

void Knight::accept(NPC* attacker, const int& distance) {
    if (alive && dynamic_cast<Squirrel*>(attacker)) {
        bool win = is_close(*attacker, distance);
        if (win) 
            alive = false;
        notify(attacker, win);
    }
}

std::ostream& operator<<(std::ostream& out, const Knight& other) {
    return out << "Knight " << other.name << " {" << other.x << ", " << other.y << '}';
}