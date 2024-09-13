
#include "test_procces_thread.cpp"

int main(int argc, char* argv[]) {
    switch (stoi(argv[1])) {
        case 1:
            return 0;
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
