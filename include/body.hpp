#ifndef BODY_HPP
#define BODY_HPP

#include <cmath>
#include <raylib.h>
#include <string>


class BodyParams {
public:
    std::string name = "";
    Vector2 center = {NAN, NAN};
    Vector2 velocity = {NAN, NAN};
    Vector2 acceleration = {NAN, NAN};
    float mass = NAN;
    float radius = NAN;
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

    void setParameters(const BodyParams& params);

public:
    // Getters
    const std::string getName() const;

    Vector2 getCenter() const;

    Vector2 getVelocity() const;

    Vector2 getAcceleration() const;

    float getMass() const;

    float getRadius() const;

    void display(int scale) const;

    friend class TestBody;
    friend class BodyPhysics;
    friend class Space;

    Body(const BodyParams& params);
};

#endif
