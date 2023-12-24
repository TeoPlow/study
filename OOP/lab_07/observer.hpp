#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <shared_mutex>

class NPC;

class Observer {
public:
    Observer() = default;
    virtual void update(NPC*, NPC*, bool) = 0;
};

class ConsoleObserver: public Observer {
    std::shared_mutex* m_mtx;
public:
    ConsoleObserver(std::shared_mutex*);
    void update(NPC*, NPC*, bool) override;
};

class FileObserver: public Observer {
    std::unique_ptr<std::ostream> _stream;
public:
    FileObserver(std::ofstream&);
    
    void update(NPC*, NPC*, bool) override;
};
