#include "space.hpp"
#include "body.hpp"
#include <algorithm>

void Space::addBody(Body body) {
    body.setName(defaultNameforEmpty(body.getName()));
    body.setName(generateUniqueName(body.getName()));
    bodies.push_back(body);

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

void Space::delBody(Body* targetBody) {
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
        if (&(*it) == targetBody) {
            bodies.erase(it);
            break;
        }
    }
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

std::string Space::getBodyNameByPoint(Vector2 point) {
    for (auto &body : bodies) {
        if (CheckCollisionCircles(body.getCenter(), 50, point, 4)){  //TODO: that's smells dirty
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
void Space::displayAll(){
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
        it->display();
    }
}
