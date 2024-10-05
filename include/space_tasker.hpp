#ifndef SPACE_TASKER_HPP
#define SPACE_TASKER_HPP
#include "space.hpp"
#include "thread.hpp"
#include <atomic>
#include <thread>

#define DEFAULT_CALCULATIONS_PER_SECOND 100


class SpaceTasker{
public:
    SpaceTasker(TaskThread& _spacethread, Space& _space);
    ~SpaceTasker();
    void AddBody(Body body);
    void setCanculationsPerSecond(int amount);
    int getCanculationsPerSecond();
private:
    int canculations_per_second = DEFAULT_CALCULATIONS_PER_SECOND;
    void delayedUpdate();
    thread th;
    Space& space;
    TaskThread& taskthread;
    atomic<bool> running;
};


#endif
