#ifndef PROCESS_BODIES_HPP
#define PROCESS_BODIES_HPP

#include <string>
#include "raylib.h"
#include <vector>
#include <thread>
#include <mutex>


#define CALCULATIONS_PER_SECOND 100
#define DELTA_TIME_IN_SECONDS 1


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
    std::mutex bodiesMutex;

    void updateBodies();

public:
    Bodies();
    ~Bodies();
    void addBody(const Body& body);
    Body* getBodyByName(const std::string& name);
    void drawAll() const;
    void addImpulseToBody(Body* body, Vector2 impulse);
    std::vector<std::string> SortedNamesByKeyword(const std::string& query);
    int getBodyCount(void);
    std::string getBodyNameByPoint(Vector2 point);
};
#endif