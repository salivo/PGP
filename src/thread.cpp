
#include "thread.hpp"
#include <mutex>
#include <thread>

using namespace std;

void TaskQueue::addTask(function<void()> func){
    {
        lock_guard<mutex> lock(queueMutex);
        tasks.push(func);
    }
    taskAvailable.notify_one();
}

void TaskQueue::executeTask(){
    std::function<void()> task;
        {
            lock_guard<mutex> lock(queueMutex);
            if (tasks.empty()) {
                return;
            }
            task = std::move(tasks.front());
            tasks.pop();
        }
        if (task) {
            task();
        }
};

bool TaskQueue::hasTasks() {
    lock_guard<mutex> lock(queueMutex);
    return !tasks.empty();
}


TaskThread::TaskThread(){
    running = true;
    th = std::thread(&TaskThread::threadloop, this);
}

TaskThread::~TaskThread() {
    {
        lock_guard<mutex> lock(taskMutex);
        running = false;
    }
    taskAvailable.notify_all();
    if (th.joinable()) {
        th.join();
    }
}

void TaskThread::threadloop(){
    while (running) {
        std::unique_lock<mutex> lock(taskMutex);
        taskAvailable.wait(lock, [this] {
            return hasTasks() || !running;
        });

        if (hasTasks()) {
            lock.unlock();
            executeTask();
        }
    }
}
bool TaskThread::isRunning(){
    return running;
}
