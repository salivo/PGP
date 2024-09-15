#ifndef TEST_BODIES_H
#define TEST_BODIES_H
#include "bodies.hpp"

int Vector2Equals2Vector(Vector2 vector_a, Vector2 vector_b);
int BodyEquals2Body(Body body_a, Body body_b);

const string test_body_name = "test name";
const Vector2 test_body_center = {10,20};
const Vector2 test_body_velocity = {2,0};
const Vector2 test_body_acceleration = {0,1};
const MassRadius test_body_massradius = {10, 5};
const Body test_body = Body(test_body_name, test_body_center, test_body_velocity, test_body_acceleration, test_body_massradius);
const Body test_body_empty_name = Body("", test_body_center, test_body_velocity, test_body_acceleration, test_body_massradius);

class Test_Bodies: public Bodies {
private:
    int isBodyAccessibleAfterAdd();
    int isRandomNamesWorks();
    int isDefaultName();
public:
    int all();
    int addBody_getBody();
    int Check_canculatePhysics();
    int Check_addImpulseToBody();
    int checkDelta();
};

#endif
