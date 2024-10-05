
#include "body.hpp"
#include <deque>
#include <raylib.h>
#define DEFAULT_DELTA 1.0f

class BodyPhysics{
private:
    float delta = DEFAULT_DELTA;
protected:
    void applyPhysics(std::deque<Body>& bodies);
    Vector2 calculateVelocity(const Body& body);
    Vector2 calculatePosition(const Body& body);
    void addImpulse(Vector2 impulse);
public:
    friend class Space;
    void setDelta(float delta);
    float getDelta();
};
