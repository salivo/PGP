#include "test_space.hpp"
#include "body.hpp"
#include "space.hpp"

#include "test_body.hpp"


int TestSpace::runAll() {
    if(checkAddRem()) return 1;
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
    s.delBody(b);
    b = s.getBodyByName(test_body_params.name);
    if (b != nullptr) return 1;
    return 0;
}
