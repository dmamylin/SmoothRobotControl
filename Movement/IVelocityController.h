#ifndef MOVEMENT_STRATEGY_H
#define MOVEMENT_STRATEGY_H

#include "../Utilities/MathLib/Types.h"

class IVelocityController {
public:
    virtual ~IVelocityController() {}

    virtual f64 getLinearVelocity() const = 0;
    virtual f64 getAngularVelocity() const = 0;

    virtual void run(f64 distanceToTarget, f64 headingAngle,
        f64 targetHeadingAngle) = 0;
};

#endif