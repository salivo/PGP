
#include "process_bodies.hpp"


#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>


Bodies::Bodies() : running(true), updateThread(&Bodies::updateBodies, this) {}

Bodies::~Bodies() {
    running = false;
    if (updateThread.joinable()) {
        updateThread.join();
    }
}

void Bodies::updateBodies() {
    while (running) {
        std::lock_guard<std::mutex> lock(bodiesMutex);
        for (auto &body : bodies) {
            body.velocity = Vector2Add(body.velocity, Vector2Scale(body.acceleration, DELTA_TIME_IN_SECONDS));
            body.center = Vector2Add(body.center, Vector2Scale(body.velocity, DELTA_TIME_IN_SECONDS));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / CALCULATIONS_PER_SECOND));
    }
}

void Bodies::addBody(const Body& body) {
    std::lock_guard<std::mutex> lock(bodiesMutex);
    bodies.push_back(body);
}

Body* Bodies::getBodyByName(const std::string& name) {
    // std::lock_guard<std::mutex> lock(bodiesMutex);
    for (auto &body : bodies) {
        if (body.name == name) {
            return &body;
        }
    }
    return nullptr;
}

void Bodies::drawAll() const {
    for (const auto& body : bodies) {
        DrawCircleV(body.center, 50, MAROON);
    }
}

void Bodies::addImpulseToBody(Body* body, Vector2 impulse) {
    std::lock_guard<std::mutex> lock(bodiesMutex);
    float deltaTimeInSeconds = GetFrameTime();
    body->velocity = Vector2Add(body->velocity, Vector2Scale(impulse, deltaTimeInSeconds / body->massradius.mass));
}

std::vector<std::string> Bodies::SortedNamesByKeyword(const std::string& query) {
    std::vector<std::string> filtered_bodies;
    for (auto &body : bodies) {
        if (body.name.find(query) != std::string::npos) {
            filtered_bodies.push_back(body.name);
        }
    }
    return filtered_bodies;

}

int Bodies::getBodyCount(void){
    return bodies.size();
}

std::string Bodies::getBodyNameByPoint(Vector2 point){
    for (auto &body : bodies) {
        if (CheckCollisionCircles(body.center, 50, point, 4)){
            return body.name;
        }
    }
    return "";
}
