#include "test_space.hpp"
#include "body.hpp"
#include "space.hpp"

#include "test_body.hpp"


int TestSpace::runAll() {
    if(checkAddRem()) return 1;
    if(checkParamSetting()) return 1;
    return 0; // TODO
}

int TestSpace::checkAddRem(){
    int err = 0;
    Space s = Space();
    // check adding
    s.addBody(Body(test_body_params));
    Body* b = s.getBodyByName(test_body_params.name);
    if (b == nullptr) return 1;
    if (cmpBody2Param(*b, test_body_params)) return 1;

    //check deleting
    s.delBody(b->getName());
    b = s.getBodyByName(test_body_params.name);
    if (b != nullptr) return 1;
    return 0;
}

int TestSpace::checkParamSetting(){
    Space s = Space();
    s.addBody(Body(test_body_params));
    Body* b = s.getBodyByName(test_body_params.name);
    s.setParameters(b, {.name = "name"});
    if (b->getName() != "name") return 1;
    s.setParameters(b, {.center {123, NAN}});
    if (b->getCenter().x != 123) return 1;
    if (b->getCenter().y != test_body_params.center.y) return 1;
    s.setParameters(b, {.center {NAN, 321}});
    if (b->getCenter().x != 123) return 1;
    if (b->getCenter().y != 321) return 1;
    s.setParameters(b, {.center {456,654}});
    if (b->getCenter().x != 456) return 1;
    if (b->getCenter().y != 654) return 1;
    if (b->getName() != "name") return 1;

    return 0;
}
