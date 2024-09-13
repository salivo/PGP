
#include "process_thread.hpp"
#include <optional>

using namespace std;

void CommandQueue::add(Command command){
    commands.push(command);
}

optional<Command> CommandQueue::get(){
    if (!commands.empty()) {
        Command cmd = commands.front();
        commands.pop();
        return cmd;
    }
    return std::nullopt;
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
