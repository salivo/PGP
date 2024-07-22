#ifndef PROCESS_BODIES_HPP
#define PROCESS_BODIES_HPP

#include <string>
#include "raylib.h"
#include <vector>
#include <thread>
#include <mutex>


#define CALCULATIONS_PER_SECOND 100
#define DELTA_TIME_IN_SECONDS 1

struct MassRadius : public Vector2 {
    MassRadius(float m, float r) : mass(x), radius(y) {
        x = m;
        y = r;
    }

    float mass;
    float radius;
};

struct Body {
    std::string name;
    Vector2 center;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 force; // I need this?
    MassRadius massradius;
    Body(std::string _name, Vector2 _center, Vector2 _velocity, Vector2 _acceleration, MassRadius _massradius)
        : name(_name), center(_center), velocity(_velocity), acceleration(_acceleration), massradius(_massradius) {}
};

class Bodies {
private:
    std::vector<Body> bodies;
    std::thread updateThread;
    bool running;
    std::mutex bodiesMutex;

    void updateBodies();
    std::string generateUniqueName(const std::string& baseName);

public:
    Bodies();
    ~Bodies();
    Body* addBody(Body body);
    Body* getBodyByName(const std::string& name);
    void drawAll() const;
    void addImpulseToBody(Body* body, Vector2 impulse);
    std::vector<std::string> SortedNamesByKeyword(const std::string& query);
    int getBodyCount(void);
    std::string getBodyNameByPoint(Vector2 point);
    void deleteBody(Body* targetBody);
};
#endif
