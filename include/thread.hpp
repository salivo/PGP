#ifndef PROCESS_BODIES_HPP
#define PROCESS_BODIES_HPP

#include <atomic>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class TaskQueue {
private:
    queue<function<void()>> tasks;
public:
    condition_variable taskAvailable;
    mutex queueMutex;
    void addTask(function<void()> func);
    void executeTask();
    bool hasTasks();
};

class TaskThread : public TaskQueue {
private:
    atomic<bool> running;
    thread th;
    mutex taskMutex;
    void threadloop();

public:
    TaskThread();
    ~TaskThread();
    bool isRunning();
    void stop();
};

#endif
