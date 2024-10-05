#include "physics.hpp"
#include <raymath.h>

void BodyPhysics::applyPhysics(std::deque<Body>& bodies) {
    for (Body& body : bodies) {
        body.setVelocity(calculateVelocity(body));
        body.setCenter(calculatePosition(body));
    }
}
Vector2 BodyPhysics::calculateVelocity(const Body& body) {
    return Vector2Add(body.velocity, Vector2Scale(body.acceleration, delta));
}
Vector2 BodyPhysics::calculatePosition(const Body& body) {
    return Vector2Add(body.center, Vector2Scale(body.velocity, delta));
}

void BodyPhysics::setDelta(float delta){
    BodyPhysics::delta = delta;
}
float BodyPhysics::getDelta(){
    return delta;
}
