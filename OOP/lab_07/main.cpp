#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <thread>
#include <shared_mutex>
#include <chrono>

#include "squirrel.hpp"
#include "pegas.hpp"
#include "knight.hpp"
#include "observer.hpp"
#include "factory.hpp"

using namespace std::chrono_literals;

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager {
    std::queue<FightEvent> events;
    std::shared_mutex m_mtx;
public:
    void add_event(const FightEvent& event) {
        std::lock_guard<std::shared_mutex> addlock(m_mtx);
        events.push(event);
    }

    void operator() (std::chrono::steady_clock::time_point start_time, std::shared_mutex& mtx) {
        while (std::chrono::steady_clock::now() - start_time < 30s) {
            if (!events.empty()) {
                FightEvent current_fight;
                {
                    std::lock_guard<std::shared_mutex> poplock(m_mtx);
                    current_fight = events.front();
                    events.pop();
                }
                {
                    std::lock_guard<std::shared_mutex> fightlock(mtx);
                    if (current_fight.attacker->is_alive() && current_fight.defender->is_alive()) {
                        current_fight.defender->accept(current_fight.attacker.get());
                    }
                }
            }
            else {
                std::this_thread::sleep_for(100ms);
            }
        }
    }
};

int main() {
    constexpr int MAX_X = 50, MAX_Y = 25;

    std::shared_mutex io_mtx;

    ConsoleObserver obs(&io_mtx);
    std::ofstream logfile("log.txt");
    FileObserver fobs(logfile);

    std::vector<std::shared_ptr<NPC>> fighters;
    std::shared_mutex data_mtx;
    for (int i = 0; i < 50; ++i) {
        fighters.push_back(factory(NPC_type(std::rand() % 3),
                            std::rand() % MAX_X, std::rand() % MAX_Y));
        fighters.back()->attach(&obs);
        fighters.back()->attach(&fobs);
    }

    FightManager FM;

    auto start_time = std::chrono::steady_clock::now();


    std::thread fight_thread(std::ref(FM), start_time, std::ref(data_mtx));

    std::thread move_thread([&fighters, &data_mtx, &FM, start_time, MAX_X, MAX_Y] () {
        while (std::chrono::steady_clock::now() - start_time < 30s) {
            {
                std::lock_guard<std::shared_mutex> movelock(data_mtx);
                for (auto npc : fighters) {
                    if (npc->is_alive())
                        npc->rand_move(MAX_X, MAX_Y);
                }
            }
            {
                std::shared_lock<std::shared_mutex> readlock(data_mtx);
                for (auto attacker : fighters) {
                    for (auto defender : fighters) {
                        if (attacker->is_alive() && defender->is_alive()) {
                            if (attacker->is_close(*defender))
                                FM.add_event({attacker, defender});
                        }
                    }
                }
                
            }
            std::this_thread::sleep_for(1s);
        }
    });

    while (std::chrono::steady_clock::now() - start_time < 30s) {
        std::vector<std::vector<char>> field(MAX_Y, std::vector<char>(MAX_X, '`'));

        {
            std::shared_lock<std::shared_mutex> readlock(data_mtx);
            for (auto npc : fighters) {
                auto [x, y] = npc->get_coordinates();
                field[y][x] = npc->token();
            }
        }
        {
            std::lock_guard<std::shared_mutex> printlock(io_mtx);
            for (int i = 0; i < field.size(); ++i) {
                for (int j = 0; j < field[i].size(); ++j) {
                    std::cout << field[i][j];
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(1s);
    }

    move_thread.join();
    fight_thread.join();

    std::cout << "Выжившие:\n" << std::endl;
    for (auto npc : fighters) {
        if (npc->is_alive()) {
            npc->print(std::cout);
            std::cout << std::endl;
        }
    }
}