
#include "process_bodies.hpp"


#include <algorithm>
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

std::string Bodies::generateUniqueName(const std::string& baseName) {
    int counter = 1;
    std::string newName = baseName;

    auto nameExists = [&](const std::string& name) {
        return std::find_if(bodies.begin(), bodies.end(), [&](const Body& body) {
            return body.name == name;
        }) != bodies.end();
    };

    while (nameExists(newName)) {
        newName = baseName + "_" + std::to_string(counter);
        ++counter;
    }

    return newName;
}

Body* Bodies::addBody(Body body) {
    // std::lock_guard<std::mutex> lock(bodiesMutex);
    body.name = generateUniqueName(body.name);
    bodies.push_back(body);
    return &bodies.back();
}

Body* Bodies::getBodyByName(const std::string& name) {
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
void Bodies::deleteBody(Body* targetBody) {
    std::lock_guard<std::mutex> lock(bodiesMutex);
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
        if (&(*it) == targetBody) {
            bodies.erase(it);
            break;
        }
    }
}
