#include "bodies.hpp"

int Vector2Equals2Vector(Vector2 vector_a, Vector2 vector_b){
    if (vector_a.x != vector_b.x){
        return 1;
    }
    if (vector_a.y != vector_b.y){
        return 1;
    }
    return 0;
}

int BodyEquals2Body(Body body_a, Body body_b){
    if (body_a.name != body_b.name){
        return 1;
    }
    if (Vector2Equals2Vector(body_a.center, body_b.center)) return 1;
    if (Vector2Equals2Vector(body_a.velocity, body_b.velocity)) return 1;
    if (Vector2Equals2Vector(body_a.acceleration, body_b.acceleration)) return 1;
    if (Vector2Equals2Vector(body_a.massradius, body_b.massradius)) return 1;
    return 0;
}

string test_body_name = "test name";
Vector2 test_body_center = {10,20};
Vector2 test_body_velocity = {2,0};
Vector2 test_body_acceleration = {0,0};
MassRadius test_body_massradius = {10, 5};
Body test_body = Body(test_body_name, test_body_center, test_body_velocity, test_body_acceleration, test_body_massradius);
