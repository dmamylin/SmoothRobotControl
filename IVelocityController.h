#ifndef MOVEMENT_STRATEGY_H
#define MOVEMENT_STRATEGY_H

#include "SDL2Types.h"

class IVelocityController {
protected:
    f64 linearVelocity;
    f64 angularVelocity;

public:
    IVelocityController() :
        linearVelocity(0.0),
        angularVelocity(0.0) {}
    virtual ~IVelocityController() {}

    f64 getLinearVelocity() const { return linearVelocity; }
    f64 getAngularVelocity() const { return angularVelocity; }

    virtual void run(f64 distanceToTarget, f64 headingAngle,
        f64 targetHeadingAngle) = 0;
};

#endif