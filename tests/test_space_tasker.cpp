#include "space.hpp"
#include "space_tasker.hpp"
#include "test_body.hpp"
#include "thread.hpp"
#include "test_space_tasker.hpp"


int TestSpaceTasker::runAll(){
    Space s;
    TaskThread t;
    SpaceTasker st(t, s);
    BodyParams bp = {
        .name = "hello"
    };
    st.AddBody(Body(bp));
    delayms(1);
    if (!s.getBodyCount()) return 1;
    Body* foundBody = s.getBodyByName(bp.name);
    if (!foundBody) return 1;
    if (cmpBody2Param(*foundBody, bp)) return 1;
    return 0;
}
