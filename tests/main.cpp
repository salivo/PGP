
#include "test_bodies.cpp"
#include "test_bodies.hpp"
#include "test_process_thread.cpp"


Test_Bodies testbodies;

int main(int argc, char* argv[]) {
    switch (stoi(argv[1])) {
        case 1:
            return testbodies.all();
        break;
        case 2:
            return test_Queue();
        break;
        default:
            return 1;
        break;

    }
    return 0;
}
