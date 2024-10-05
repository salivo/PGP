#ifndef TEST_BODY_HPP
#define TEST_BODY_HPP

#include "body.hpp"
#include "testinghelpers.hpp"


static BodyParams test_body_params = {
    .name = "test_body",
    .center = {0,0},
    .velocity = {1,1},
    .acceleration = {0.5,0.5},
    .mass = 20,
    .radius = 30
};

static int cmp2Body(Body b1, Body b2){
    if (b1.getName() != b2.getName()) return 1;
    if (Vector2Equals2Vector(b1.getCenter(), b2.getCenter())) return 1;
    if (Vector2Equals2Vector(b1.getVelocity(), b2.getCenter())) return 1;
    if (Vector2Equals2Vector(b1.getCenter(), b2.getCenter()))  return 1;
    if (b1.getMass() != b2.getMass() ) return 1;
    if (b1.getRadius() != b2.getRadius()) return 1;
    return 0;
}

static int cmpBody2Param(Body b, BodyParams p){
    if (b.getName() != p.name) return 1;
    if (Vector2Equals2Vector(b.getCenter(), p.center)) return 1;
    if (Vector2Equals2Vector(b.getVelocity(), p.velocity)) return 1;
    if (Vector2Equals2Vector(b.getAcceleration(), p.acceleration))  return 1;
    if (b.getMass() != p.mass) return 1;
    if (b.getRadius() != p.radius) return 1;
    return 0;
}

class TestBody {
public:
    static int runAll();

private:
    static int validateSetingandGetting();
};


#endif
