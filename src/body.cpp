#include "body.hpp"
#include <raylib.h>
#include <raymath.h>


Body::Body(const BodyParams& params){
    BodyParams pcopy = params;
    if (std::isnan(params.center.x)){
        pcopy.center.x = 0.0;
    }
    if (std::isnan(params.center.y)){
        pcopy.center.y = 0.0;
    }
    if (std::isnan(params.velocity.x)){
        pcopy.velocity.x = 0.0;
    }
    if (std::isnan(params.velocity.y)){
        pcopy.velocity.y = 0.0;
    }
    if (std::isnan(params.acceleration.x)){
        pcopy.acceleration.x = 0.0;
    }
    if (std::isnan(params.acceleration.y)){
        pcopy.acceleration.y = 0.0;
    }
    if (std::isnan(params.mass)){
        pcopy.mass = 0.0;
    }
    if (std::isnan(params.radius)){
        pcopy.radius = 0.0;
    }
    name = pcopy.name;
    center = pcopy.center;
    velocity = pcopy.velocity;
    acceleration = pcopy.acceleration;
    mass = pcopy.mass;
    radius = pcopy.radius;
}

void Body::setParameters(const BodyParams &params){
    name = params.name;
    center = params.center;
    velocity = params.velocity;
    acceleration = params.acceleration;
    mass = params.mass;
    radius = params.radius;
}

void Body::setName(const std::string& name) {
    this->name = name;
}

void Body::setCenter(Vector2 center) {
    this->center = center;
}

void Body::setVelocity(Vector2 velocity) {
    this->velocity = velocity;
}

void Body::setAcceleration(Vector2 acceleration) {
    this->acceleration = acceleration;
}

void Body::setMass(float mass) {
    this->mass = mass;
}

void Body::setRadius(float radius) {
    this->radius = radius;
}

const std::string Body::getName() const {
    return name;
}

Vector2 Body::getCenter() const {
    return center;
}

Vector2 Body::getVelocity() const {
    return velocity;
}

Vector2 Body::getAcceleration() const {
    return acceleration;
}

float Body::getMass() const {
    return mass;
}

float Body::getRadius() const {
    return radius;
}

void Body::display(int scale) const {
    Vector2 pixels_center = Vector2Scale(center, 1.0/scale);
    DrawCircleV(pixels_center, radius/scale, MAROON);
}
