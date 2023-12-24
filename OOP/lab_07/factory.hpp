#include "NPC.hpp"

std::shared_ptr<NPC> factory(std::istream&);
std::shared_ptr<NPC> factory(const std::string&, const int&, const int&);
std::shared_ptr<NPC> factory(const NPC_type, const int&, const int&);