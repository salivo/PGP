
#ifndef BODIES_HPP
#define BODIES_HPP

#include <string>
#include "raylib.h"
#include <vector>

using namespace std;

#define DEFAULT_NAME "NewBody"
#define DEFAULT_DELTA 1.0f

struct MassRadius : public Vector2 {
    MassRadius(float m, float r) : mass(x), radius(y) {
        x = m;
        y = r;
    }

    float mass;
    float radius;
};


struct Body {
    string name;
    Vector2 center;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 force; // I need this?
    MassRadius massradius;
    Body(string _name, Vector2 _center, Vector2 _velocity, Vector2 _acceleration, MassRadius _massradius)
        : name(_name), center(_center), velocity(_velocity), acceleration(_acceleration), massradius(_massradius) {}
};


class Bodies {
private:
    vector<Body> bodies;
    string generateUniqueName(const string& baseName);
    string defaultNameforEmpty(const string& baseName);
    float delta = DEFAULT_DELTA;
protected:
    void CanculatePhysics();
    Body* addBody(Body body);
    void addImpulseToBody(Body* body, Vector2 impulse);
    void setDelta(float delta);
    float getDelta();
public:
    Body* getBodyByName(const string& name);
    void drawAll() const;
    vector<string> SortedNamesByKeyword(const string& query);
    int getBodyCount(void);
    string getBodyNameByPoint(Vector2 point);
    void deleteBody(Body* targetBody);

    friend class Test_Bodies;
};
#endif
