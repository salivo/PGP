#include "space_tasker.hpp"
#include "body.hpp"


void SpaceTasker::delayedUpdate() {
    while (running) {
    this_thread::sleep_for(
        chrono::milliseconds(1000 / canculations_per_second));
    taskthread.addTask(
        [this](){
            space.update();
        }
    );
    }
}

SpaceTasker::SpaceTasker(TaskThread& _spacethread, Space& _space) :
    taskthread(_spacethread), space(_space)
{
    running = true;
    th = thread(&SpaceTasker::delayedUpdate, this);
}

void SpaceTasker::AddBody(Body body){
    taskthread.addTask(
        [this, body](){
            space.addBody(body);
        }
    );
}

SpaceTasker::~SpaceTasker(){
    running = false;
    if(th.joinable()){
        th.join();
    }
}

void SpaceTasker::setCanculationsPerSecond(int amount){
    if (amount<=0) return;
    canculations_per_second = amount;
}
int SpaceTasker::getCanculationsPerSecond(){
    return canculations_per_second;
}
