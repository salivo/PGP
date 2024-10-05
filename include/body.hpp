#ifndef BODY_HPP
#define BODY_HPP

#include <raylib.h>
#include <string>

class BodyParams {
public:
    std::string name;
    Vector2 center = {0, 0};
    Vector2 velocity = {0, 0};
    Vector2 acceleration = {0, 0};
    float mass = 0.0f;
    float radius = 0.0f;
};

class Body {
private:
    std::string name;
    Vector2 center;
    Vector2 velocity;
    Vector2 acceleration;
    float mass;
    float radius;

protected:
    void setName(const std::string& name);

    void setCenter(Vector2 center);

    void setVelocity(Vector2 velocity);

    void setAcceleration(Vector2 acceleration);

    void setMass(float mass);

    void setRadius(float radius);

public:
    // Getters
    const std::string getName() const;

    Vector2 getCenter() const;

    Vector2 getVelocity() const;

    Vector2 getAcceleration() const;

    float getMass() const;

    float getRadius() const;

    void display() const;

    friend class TestBody;
    friend class BodyPhysics;

    Body(const BodyParams& params)
        : name(params.name), center(params.center), velocity(params.velocity),
          acceleration(params.acceleration), mass(params.mass), radius(params.radius) {}
};

#endif
