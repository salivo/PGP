#ifndef PROCESS_BODIES_HPP
#define PROCESS_BODIES_HPP

#include <optional>
#include <queue>
#include <raylib.h>
#include <thread>
#include <string>
#include "bodies.hpp"

#define CALCULATIONS_PER_SECOND 100
#define DELTA_TIME_IN_SECONDS 1

using namespace std;

enum Actions{
    ADD_BODY,
    DEL_BODY,
};

struct Command{
    Actions action;
    Body subject;
    string parameter;
    Command(Actions _action, Body _subject, string _parameter):
        action(_action), subject(_subject), parameter(_parameter) {}
};


class CommandQueue{
private:
    queue<Command> commands;
public:
    void add(Command command);
    optional<Command> get();
};


class ProcessBodies: public Bodies, public CommandQueue{
private:
    bool running = false;
    thread updateThread;
    void threadloop();
public:
    void start();
};

#endif
