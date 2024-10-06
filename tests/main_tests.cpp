#include "space.hpp"
#include "space_tasker.hpp"
#include "test_body.hpp"
#include "test_space.hpp"
#include "test_space_tasker.hpp"
#include "test_thread.hpp"
#include "testinghelpers.hpp"
#include "thread.hpp"
#include <string>

using namespace std;

int TestALLModular(){
    Space s;
    TaskThread t;
    SpaceTasker st(t, s);
    delayms(1);
    s.physics.setDelta(1);
    st.setCanculationsPerSecond(10);
    BodyParams bp = test_body_params;
    bp.name = "hello";
    bp.center = {0,0};
    bp.velocity = {1,0};
    bp.acceleration = {0,0};
    st.AddBody(Body(bp));
    delayms(100);
    Body* foundBody = s.getBodyByName(bp.name);
    if (!foundBody) return 1;
    if (foundBody->getCenter().x != 1) return 1;
    return 0;
}


int main(int argc, char* argv[]) {
    switch (stoi(argv[1])) {
        case 1:
            return TestBody::runAll();
        break;
        case 2:
            return TestSpace::runAll();
        break;
        case 3:
            return TestThread::runAll();
        break;
        case 4:
            return TestSpaceTasker::runAll();
        break;
        case 5:
            return TestALLModular();
        break;
        default:
            return 1;
        break;

    }
    return 0;
}
