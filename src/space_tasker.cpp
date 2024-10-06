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

void SpaceTasker::AddBody(Body body, std::shared_ptr<std::string> bodyName){
    taskthread.addTask(
        [this, body, bodyName](){
            string name = space.addBody(body);
            if (bodyName != nullptr){
                *bodyName = name;
            }
        }
    );
}

void SpaceTasker::DelBody(const std::string& name){
    taskthread.addTask(
        [this, name](){
            space.delBody(name);
        }
    );
}

void SpaceTasker::setParams(Body* body, const BodyParams& params) {
    taskthread.addTask(
        [this, body, params](){
            space.setParameters(body, params);
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
