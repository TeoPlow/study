#include "factory.hpp"
#include "squirrel.hpp"
#include "pegas.hpp"
#include "knight.hpp"

std::shared_ptr<NPC> factory(std::istream& in) {
    std::string type;
    int x, y;
    char c;
    in >> type >> c >> x >> c >> y >> c;
    std::shared_ptr<NPC> res;
    if (type == "Squirrel") {
        res = std::make_shared<Squirrel>(x, y);
    }
    else if (type == "Pegas") {
        res = std::make_shared<Pegas>(x, y);
    }
    else if (type == "Knight") {
        res = std::make_shared<Knight>(x, y);
    }
    else if (type != "") {
        std::cerr << "Unknown type" << std::endl;
    }
    return res;
}

std::shared_ptr<NPC> factory(const std::string& type, const int& x, const int& y) {
    std::shared_ptr<NPC> res;
    if (type == "Squirrel") {
        res = std::make_shared<Squirrel>(x, y);
    }
    else if (type == "Pegas") {
        res = std::make_shared<Pegas>(x, y);
    }
    else if (type == "Knight") {
        res = std::make_shared<Knight>(x, y);
    }
    else {
        std::cerr << "Unknown type" << std::endl;
    }
    return res;
}

std::shared_ptr<NPC> factory(const NPC_type type, const int& x, const int& y) {
    std::shared_ptr<NPC> res;

    switch (type)
    {
    case NPC_type::squirrel:
        res = std::make_shared<Squirrel>(x, y);
        break;
    case NPC_type::pegas:
        res = std::make_shared<Pegas>(x, y);
        break;
    case NPC_type::knight:
        res = std::make_shared<Knight>(x, y);
        break;
    }
    return res;
}
