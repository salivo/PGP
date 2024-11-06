#include "body.hpp"
#include "space.hpp"
#include "space_tasker.hpp"
#include "test_body.hpp"
#include "testinghelpers.hpp"
#include "thread.hpp"
#include <raylib.h>
#include "test_space_tasker.hpp"


int TestSpaceTasker::runAll(){
    Space s;
    TaskThread t;
    SpaceTasker st(t, s);
    BodyParams bp = test_body_params;
    bp.name = "hello";
    st.AddBody(Body(bp));
    delayms(1);
    if (!s.getBodyCount()) return 1;
    Body* foundBody = s.getBodyByName(bp.name);
    if (!foundBody) return 1;
    if (cmpBody2Param(*foundBody, bp)) return 1;
    Vector2 newCenter = {345, 654};
    st.setParams(s.getBodyByName(bp.name), {.center = newCenter});
    delayms(1);
    if (Vector2Equals2Vector(s.getBodyByName(bp.name)->getCenter(), newCenter)) return 1;
    st.setParams(s.getBodyByName(bp.name), {.name = "nothello"});
    delayms(1);
    if (foundBody->getName() != "nothello") return 1;
    st.DelBody(foundBody->getName());
    if (s.getBodyCount() == 0) return 1;

    return 0;
}
