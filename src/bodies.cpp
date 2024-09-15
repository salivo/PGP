
#include <algorithm>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>

#include "bodies.hpp"

string Bodies::generateUniqueName(const string& baseName) {
    int counter = 1;
    string newName = baseName;

    auto nameExists = [&](const string& name) {
        return find_if(bodies.begin(), bodies.end(), [&](const Body& body) {
            return body.name == name;
        }) != bodies.end();
    };

    while (nameExists(newName)) {
        newName = baseName + "_" + to_string(counter);
        ++counter;
    }

    return newName;
}

string Bodies::defaultNameforEmpty(const string& baseName){
    if (baseName == ""){
        return DEFAULT_NAME;
    }
    return baseName;
}

Body* Bodies::addBody(Body body) {
    body.name = defaultNameforEmpty(body.name);
    body.name = generateUniqueName(body.name);
    bodies.push_back(body);
    return &bodies.back();
}

Body* Bodies::getBodyByName(const string& name) {
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

void Bodies::CanculatePhysics(int delta){
    for (auto &body : bodies) {
        body.velocity = Vector2Add(body.velocity, Vector2Scale(body.acceleration, delta));
        body.center = Vector2Add(body.center, Vector2Scale(body.velocity, delta));
    }
}


void Bodies::addImpulseToBody(Body* body, Vector2 impulse) {
    float deltaTimeInSeconds = GetFrameTime();
    body->velocity = Vector2Add(body->velocity, Vector2Scale(impulse, deltaTimeInSeconds / body->massradius.mass));
}

vector<string> Bodies::SortedNamesByKeyword(const string& query) {
    vector<string> filtered_bodies;
    for (auto &body : bodies) {
        if (body.name.find(query) != string::npos) {
            filtered_bodies.push_back(body.name);
        }
    }
    return filtered_bodies;

}

int Bodies::getBodyCount(void){
    return bodies.size();
}

string Bodies::getBodyNameByPoint(Vector2 point){
    for (auto &body : bodies) {
        if (CheckCollisionCircles(body.center, 50, point, 4)){
            return body.name;
        }
    }
    return "";
}
void Bodies::deleteBody(Body* targetBody) {
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
        if (&(*it) == targetBody) {
            bodies.erase(it);
            break;
        }
    }
}
