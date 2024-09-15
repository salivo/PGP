#include "test_bodies.hpp"
#include <raylib.h>

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


int Test_Bodies::check_all(){
    if(!check_BodyAccessibleAfterAdd()) return 1;
    if(!check_RandomNamesWorks()) return 1;
    if(check_BodyCount()) return 1;
    if(check_RemoveBody()) return 1;
    if(check_canculatePhysics()) return 1;
    if(check_Delta()) return 1;
    if(check_AddImpulse()) return 1;
    return 0;
}





int Test_Bodies::check_BodyAccessibleAfterAdd(){
    Bodies bodies;
    bodies.addBody(test_body);
    if (bodies.getBodyByName(test_body.name) == nullptr){
        return 0;
    }
    return 1;
}

int Test_Bodies::check_RandomNamesWorks(){
    Bodies bodies;
    bodies.addBody(test_body);
    bodies.addBody(test_body);
    if (bodies.getBodyByName(test_body.name + "_1") == nullptr){
        return 0;
    }
    return 1;
}

int Test_Bodies::check_DefaultName(){
    Bodies bodies;
    Body* created_body = bodies.addBody(test_body_empty_name);
    if (created_body->name == ""){
        return 0;
    }
    return 1;
}

int Test_Bodies::check_BodyCount(){
    Bodies b;
    for (int i=0; i<BODY_TEST_COUNT; i++){
        b.addBody(test_body_empty_name);
    }
    if (b.getBodyCount() != BODY_TEST_COUNT) return 1;
    return 0;
}

int Test_Bodies::check_RemoveBody(){
    Bodies b;
    for (int i=0; i<BODY_TEST_COUNT; i++){
        b.addBody(test_body_empty_name);
    }
    Body* bodytodelete = b.addBody(test_body_empty_name);
    b.deleteBody(bodytodelete);
    if (b.getBodyCount() != BODY_TEST_COUNT) return 1;
    return 0;
}

int Test_Bodies::check_canculatePhysics(){
    Bodies bodies;
    Body* body =  bodies.addBody(test_body);
    bodies.setDelta(10);
    CanculatePhysics();
    if (Vector2Equals2Vector(body->velocity, {2, 10}) == 0){
        return 1;
    }
    if (Vector2Equals2Vector(body->center, {30, 120}) == 0){
        return 1;
    }
    return 0;
}

int Test_Bodies::check_Delta(){
    Bodies b;
    b.setDelta(-1.0);
    if ( b.getDelta() < 0) return 1;
    b.setDelta(10.0);
    if (b.getDelta() != 10.0) return 1;
    return 0;
}

int Test_Bodies::check_AddImpulse(){
    Bodies b;
    Body* body =  b.addBody(test_body);
    b.setDelta(10.0);
    b.addImpulseToBody(body, {0, 1});
    if(!Vector2Equals2Vector(body->velocity, {2,1})) return 1;
    return 0;
}
