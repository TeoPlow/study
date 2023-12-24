#pragma once
#include <list>
#include <memory>
#include "observer.hpp"


class Squirrel;
class Pegas;
class Knight;

class NPC {
protected:
    std::list<Observer*> observers;
    int x;
    int y;
    std::string name;
    bool alive;
public:
    NPC() = default;
    ~NPC() = default;

    virtual void print(std::ostream&) = 0;

    virtual void accept(NPC*, const int&) = 0;

    virtual void attach(Observer*);
    virtual void detach(Observer*);
    virtual void notify(NPC*, bool);

    virtual bool is_close(const NPC&, const int&) const noexcept;
    virtual bool is_alive() const noexcept;

    friend std::ostream& operator<<(std::ostream&, const NPC&);
};