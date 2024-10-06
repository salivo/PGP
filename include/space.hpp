#ifndef SPACE_HPP
#define SPACE_HPP

#include <deque>
#include <raylib.h>
#include <string>
#include <vector>

#include "body.hpp"
#include "physics.hpp"

#define DEFAULT_NAME "NewBody"

class Space{
    private:
        std::deque<Body> bodies;
        std::string generateUniqueName(const std::string& baseName);
        std::string defaultNameforEmpty(const std::string& baseName);
    protected:
        void addBody(Body body);
        void delBody(Body* targetBody);
    public:
        BodyPhysics physics;
        int getBodyCount();
        Body *getBodyByName(std::string name);
        std::string getBodyNameByPoint(Vector2 point);
        std::vector<std::string> SortedNamesByKeyword(const std::string& query);
        void update();
        void displayAll();
        friend class SpaceTasker;
        friend class TestSpace;
};


#endif
