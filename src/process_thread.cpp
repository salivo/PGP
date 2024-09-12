
#include "process_thread.hpp"
#include <cstddef>

using namespace std;

void CommandQueue::add(Command command){
    commands.push(command);
}
Command CommandQueue::get(){
    return Command(ADD_BODY, "", "");
};


void ProcessBodies::threadloop(){
    while (true){
        this_thread::sleep_for(chrono::milliseconds(1000 / CALCULATIONS_PER_SECOND));
        CanculatePhysics(DELTA_TIME_IN_SECONDS);
    }
}

void ProcessBodies::start(){
    running = true;
}
