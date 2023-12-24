#pragma once
#include <list>
#include <memory>
#include "observer.hpp"

enum class NPC_type {
    squirrel,
    pegas,
    knight
};


class Squirrel;
class Pegas;
class Knight;

class NPC {
protected:
    std::list<Observer*> observers;
    int x;
    int y;
    bool alive;
public:
    NPC() = default;
    ~NPC() = default;

    virtual void print(std::ostream&) = 0;

    virtual void accept(NPC*) = 0;
    virtual bool attack(Squirrel&);
    virtual bool attack(Pegas&);
    virtual bool attack(Knight&);

    virtual void attach(Observer*);
    virtual void detach(Observer*);
    virtual void notify(NPC*, bool);

    virtual bool is_close(const NPC&) const noexcept = 0;
    virtual bool is_alive() const noexcept;

    virtual std::pair<int, int> get_coordinates() const noexcept;
    virtual char token() const noexcept;
    virtual void rand_move(const int& max_x = 1e9, const int& max_y = 1e9) = 0;

    friend std::ostream& operator<<(std::ostream&, const NPC&);
};