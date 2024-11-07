#include "space.hpp"
#include "body.hpp"
#include <algorithm>
#include <raylib.h>
#include <raymath.h>
#include <string>

std::string Space::addBody(Body body) {
    body.setName(defaultNameforEmpty(body.getName()));
    body.setName(generateUniqueName(body.getName()));
    bodies.push_back(body);
    return body.getName();
}

std::string Space::generateUniqueName(const std::string& baseName) {
    int counter = 1;
    std::string newName = baseName;

    auto nameExists = [&](const std::string& name) {
        return std::find_if(bodies.begin(), bodies.end(), [&](const Body& body) {
            return body.getName() == name;
        }) != bodies.end();
    };

    while (nameExists(newName)) {
        newName = baseName + "_" + std::to_string(counter);
        ++counter;
    }

    return newName;
}

std::string Space::defaultNameforEmpty(const std::string& baseName){
    if (baseName == ""){
        return DEFAULT_NAME;
    }
    return baseName;
}

void Space::delBody(const std::string& name) {
    bodies.erase(std::remove_if(bodies.begin(), bodies.end(),
        [&name](const Body& body) {
            return body.getName() == name; // Compare the names
        }), bodies.end());
}

void Space::setParameters(Body* body, const BodyParams &params){
    BodyParams pcopy = params;
    if (pcopy.name == ""){
        pcopy.name = body->getName();
    }
    if (std::isnan(params.center.x)){
        pcopy.center.x = body->getCenter().x;
    }
    if (std::isnan(params.center.y)){
        pcopy.center.y = body->getCenter().y;
    }
    if (std::isnan(params.velocity.x)){
        pcopy.velocity.x = body->getVelocity().x;
    }
    if (std::isnan(params.velocity.y)){
        pcopy.velocity.y = body->getVelocity().y;
    }
    if (std::isnan(params.acceleration.x)){
        pcopy.acceleration.x = body->getAcceleration().x;
    }
    if (std::isnan(params.acceleration.y)){
        pcopy.acceleration.y = body->getAcceleration().y;
    }
    if (std::isnan(params.mass)){
        pcopy.mass = body->getMass();
    }
    if (std::isnan(params.radius)){
        pcopy.radius = body->getRadius();
    }
    body->setParameters(pcopy);
}


int Space::getBodyCount(){
    return bodies.size();
}

Body* Space::getBodyByName(std::string name) {
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
        if (it->getName() == name) {
            return &(*it);
        }
    }
    return nullptr;
}

std::string Space::getBodyNameByPoint(Vector2 point, Scales scales) {
    for (auto &body : bodies) {
        if (CheckCollisionCircles(
            Vector2Scale(body.getCenter(), 1.0/scales.distance_scale),
            body.getRadius()/scales.size_scale,
            point,
            GET_BY_POINT_THRESHOLD
        )){
            return body.getName();
        }
    }
    return "";
}

std::vector<std::string> Space::SortedNamesByKeyword(const std::string& query) {
    std::vector<std::string> filtered_bodies;
    for (auto &body : bodies) {
        if (body.getName().find(query) != std::string::npos) {
            filtered_bodies.push_back(body.getName());
        }
    }
    return filtered_bodies;
}

void Space::update(){
    physics.applyPhysics(bodies);
}
void Space::displayAll(Scales scales){
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
        it->display(scales.distance_scale, scales.size_scale);
    }
}
