#include "observer.hpp"
#include "NPC.hpp"
#include <chrono>

ConsoleObserver::ConsoleObserver(std::shared_mutex* mtx): m_mtx(mtx) {}

void ConsoleObserver::update(NPC* defender, NPC* attacker, bool win) {
    if (!win) return;

    std::lock_guard<std::shared_mutex> printlock(*m_mtx);

    std::cout << "KILL: ";
    defender->print(std::cout);
    std::cout << " was killed by ";
    attacker->print(std::cout);
    std::cout << std::endl;
}

FileObserver::FileObserver(std::ofstream& _str) {
    _stream = std::make_unique<std::ofstream>(std::move(_str));
}

void FileObserver::update(NPC* defender, NPC* attacker, bool win) {
    if (!win) return;

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&now_time);
    *_stream << std::put_time(&local_tm, "%H:%M:%S - ");

    *_stream << "KILL: ";
    defender->print(*_stream);
    *_stream << " was killed by ";
    attacker->print(*_stream);
    *_stream << std::endl;
}
