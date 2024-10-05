#include "test_thread.hpp"
#include "testinghelpers.hpp"
#include "thread.hpp"


int TestThread::runAll(){
    TaskThread tt;
    int test = 1;
    tt.addTask([&test](){test --;});
    delayms(1); // to be sure that task went
    if (test == 1) return 1;
    tt.addTask([&test](){test ++;});
    tt.addTask([&test](){test = 10;});
    delayms(1);
    if (test != 10) return 1;
    return 0;
}
