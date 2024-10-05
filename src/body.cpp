#include "body.hpp"
#include <raylib.h>

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

void Body::display() const {
    DrawCircleV(center, 50, MAROON);
    // std::cout << "center: " << center.x << " " << center.y << std::endl;
}
