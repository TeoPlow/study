#include <gtest/gtest.h>

#include <sstream>
#include <vector>
#include <memory>
#include "squirrel.hpp"
#include "pegas.hpp"
#include "knight.hpp"
#include "factory.hpp"

TEST(Constructors, Squirrel) {
    Squirrel s(0, 0, "Karatist");
    std::stringstream out;
    s.print(out);
    ASSERT_EQ(out.str(), "Squirrel Karatist {0, 0}");
}

TEST(Constructors, Pegas) {
    Pegas t(1, 1, "Zhenya");
    std::stringstream out;
    t.print(out);
    ASSERT_EQ(out.str(), "Pegas Zhenya {1, 1}");
}

TEST(Constructors, Knight) {
    Knight e(2, 2, "Vorchun");
    std::stringstream out;
    e.print(out);
    ASSERT_EQ(out.str(), "Knight Vorchun {2, 2}");
}

TEST(Fabric, basic) {
    std::vector<std::shared_ptr<NPC>> persons;
    persons.push_back(factory("Squirrel", "Name", 0, 0));
    persons.push_back(factory("Pegas", "Name", 0, 0));
    persons.push_back(factory("Knight", "Name", 0, 0));

    std::stringstream out;
    for (auto& elem : persons) {
        elem->print(out);
    }
    ASSERT_EQ(out.str(), "Squirrel Name {0, 0}Pegas Name {0, 0}Knight Name {0, 0}");
}

TEST(Fighting, basic) {
    std::vector<std::shared_ptr<NPC>> persons;
    persons.push_back(factory("Squirrel", "Name", 0, 0));
    persons.push_back(factory("Pegas", "Name", 0, 0));
    persons.push_back(factory("Knight", "Name", 0, 0));

    for (auto& defender : persons) {
        for (auto& attacker : persons) {
            defender->accept(attacker.get(), 0);
        }
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
}