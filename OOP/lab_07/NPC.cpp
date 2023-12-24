#include "NPC.hpp"
#include <algorithm>


bool NPC::attack(Squirrel&) { return false; }
bool NPC::attack(Pegas&) { return false; }
bool NPC::attack(Knight&) { return false; }

void NPC::notify(NPC* defender, bool win) {
    for (auto &elem : NPC::observers) {
        elem->update(defender, this, win);
    }
}

std::ostream& operator<<(std::ostream& out, const NPC& other) {
    return out << "$NPC {" << other.x << ", " << other.y << '}';
}

void NPC::attach(Observer* observer) {
    observers.push_back(observer);
}
void NPC::detach(Observer* observer) {
    observers.erase(
        std::find(NPC::observers.begin(), NPC::observers.end(), observer));
}

bool NPC::is_alive() const noexcept { return alive; }

std::pair<int, int> NPC::get_coordinates() const noexcept { return {x, y}; }
char NPC::token() const noexcept { return '?'; }
