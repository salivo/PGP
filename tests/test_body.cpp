#include "test_body.hpp"
#include "body.hpp"


int TestBody::runAll() {
    if (validateSetingandGetting()) return 1;
    return 0;
}

int TestBody::validateSetingandGetting(){
    Body tb = Body(test_body_params);
    if (cmpBody2Param(tb, test_body_params)) return 1;
    tb.setName("bodytest2");
    tb.setCenter({4,4});
    tb.setVelocity({5,5});
    tb.setAcceleration({6,6});
    tb.setMass(30);
    tb.setRadius(40);
    if (cmpBody2Param(tb, {"bodytest2", {4,4}, {5,5}, {6,6}, 30, 40})) return 1;
    return 0;
}
