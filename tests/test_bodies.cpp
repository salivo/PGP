#include "test_bodies.hpp"

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


int Test_Bodies::all(){
    if(addBody_getBody()) return 1;
    return 0;
}

int Test_Bodies::addBody_getBody(){
    if(!isBodyAccessibleAfterAdd()) return 1;
    if(!isRandomNamesWorks()) return 1;
    if(!checkForDefaultName()) return 1;
    return 0;
};

int Test_Bodies::isBodyAccessibleAfterAdd(){
    Bodies bodies;
    bodies.addBody(test_body);
    if (bodies.getBodyByName(test_body.name) == nullptr){
        return 0;
    }
    return 1;
}

int Test_Bodies::isRandomNamesWorks(){
    Bodies bodies;
    bodies.addBody(test_body);
    bodies.addBody(test_body);
    if (bodies.getBodyByName(test_body.name + "_1") == nullptr){
        return 0;
    }
    return 1;
}

int Test_Bodies::checkForDefaultName(){
    Bodies bodies;
    Body* created_body = bodies.addBody(test_body_empty_name);
    if (created_body->name == ""){
        return 0;
    }
    return 1;
}
