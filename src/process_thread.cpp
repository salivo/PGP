
#include "process_thread.hpp"
#include <optional>
#include <string>
#include <vector>

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
        CanculatePhysics();
    }
}

void ProcessBodies::start(){
}
