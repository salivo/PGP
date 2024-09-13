#include "process_thread.hpp"
#include "test_bodies.cpp"

#include <string>

#define MULTIPLE_COMMAND_COUNT 4

int test_queue_once(CommandQueue queue, Command test_command, std::string test_param){
    queue.add(test_command);
    auto resulted_command = queue.get();
    if ( !resulted_command ) return 1;
    if ( resulted_command->action != ADD_BODY ) return 1;
    if ( BodyEquals2Body(test_body, resulted_command->subject) ) return 1;
    if ( resulted_command->parameter != test_param ) return 1;
    return 0;
}

int test_queue_multiple(CommandQueue queue, Command test_command){
    for (int i = 0; i<MULTIPLE_COMMAND_COUNT; i++){
        queue.add(test_command);
    }
    for (int i = 0; i<MULTIPLE_COMMAND_COUNT; i++){
        auto resulted_command = queue.get();
        if ( !resulted_command ) return 1;
    }
    return 0;
}

int test_queue_if_empty(CommandQueue queue){
    auto resulted_command = queue.get();
    if ( resulted_command ) return 1;
    return 0;
}

int test_Queue() {
    CommandQueue queue = CommandQueue();
    std::string test_param = "test_parrameter";
    Command test_command = Command(ADD_BODY, test_body, test_param);
    if ( test_queue_once(queue, test_command,  test_param) ) return 1;
    if ( test_queue_if_empty(queue) ) return 1;
    if ( test_queue_multiple(queue, test_command) ) return 1;
    if ( test_queue_if_empty(queue) ) return 1;
    return 0;
}
