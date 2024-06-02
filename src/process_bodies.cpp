
#include <cstdio>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

#define CanculationPerSecond 100
#define deltaTimeInSeconds 1

struct Body {
    std::string name;
    Vector2 center;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 force;
    float mass;
    Body(std::string _name, Vector2 _center, Vector2 _velocity, Vector2 _acceleration, float _mass)
        : name(_name), center(_center), velocity(_velocity), acceleration(_acceleration), mass(_mass) {}
};

class Bodies {
private:
    std::vector<Body> bodies;
    std::thread updateThread;
    bool running;
    std::mutex bodiesMutex; // Mutex for thread safety
    void updateBodies() {
        while (running) {
            std::lock_guard<std::mutex> lock(bodiesMutex); // Lock the mutex to prevent simultaneous access to bodies vector
            for (auto &body : bodies) {
                body.velocity = Vector2Add(body.velocity, Vector2Scale(body.acceleration, deltaTimeInSeconds));
                body.center = Vector2Add(body.center, Vector2Scale(body.velocity, deltaTimeInSeconds));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000/CanculationPerSecond));
        }
    }
public:
    Bodies() : running(true), updateThread(&Bodies::updateBodies, this) {}
    ~Bodies() {
        running = false;
        if (updateThread.joinable()) {
            updateThread.join();
        }
    }
    void addBody(Body body) {
        std::lock_guard<std::mutex> lock(bodiesMutex); // Lock the mutex before modifying bodies vector
        bodies.push_back(body);
    }
    Body* getBodyByName(const std::string& name) {
        std::lock_guard<std::mutex> lock(bodiesMutex); // Lock the mutex before accessing bodies vector
        for (auto &body : bodies) {
            if (body.name == name) {
                return &body;
            }
        }
        return nullptr; // Return nullptr if body with given name is not found
    }
    void drawAll(){
        for (const auto& body : bodies) {
            DrawCircleV(body.center, 50, MAROON);
        }
    }
    void addImpulseToBody(Body* body, Vector2 impuls){
        body->velocity = Vector2Add(body->velocity, Vector2Scale(impuls, deltaTimeInSeconds/body->mass));
    }
};
