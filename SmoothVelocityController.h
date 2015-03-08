#ifndef SMOOTH_MOVEMENT_STRATEGY_H
#define SMOOTH_MOVEMENT_STRATEGY_H

#include <math.h>

#include "SDL2Types.h"
#include "IVelocityController.h"

class SmoothVelocityController : public IVelocityController {
private:
    SmoothVelocityController(const SmoothVelocityController&);

    //"Хорошие" значения: k1 = 1.0, k2 = 10.0, beta = 0.4, lambda = 2.0
    //Уменьшая k1, можно спрямить траекторию
    const f64 k1 = 1.0; //TODO: убрать все в параметры
    const f64 k2 = 10.0;
    const f64 beta = 0.4;
    const f64 lambda = 2.0;
    const f64 maxVelocity = 4.0;

    // r - distanceToTarget
    // delta - headingAngle
    // theta - targetHeadingAngle
    void computeLinearVelocity(f64 r, f64 delta, f64 theta) {
        f64 curvature = -(1.0 / r) * (k2*(delta - atan(-k1*theta)) +
            (1 + k1 / (1 + k1*k1*theta*theta))*sin(delta));
        linearVelocity = maxVelocity / (1 + beta*pow(abs(curvature), lambda));
    }

    void computeAngularVelocity(f64 r, f64 delta, f64 theta) {
        angularVelocity = (-linearVelocity / r) * (k2*(delta - atan(-k1*theta)) +
            (1 + k1 / (1 + k1*k1*theta*theta))*sin(delta));
    }

public:
    SmoothVelocityController() : IVelocityController() {}

    void run(f64 distanceToTarget, f64 headingAngle,
        f64 targetHeadingAngle) {
        computeLinearVelocity(distanceToTarget, headingAngle,
            targetHeadingAngle);
        computeAngularVelocity(distanceToTarget, headingAngle,
            targetHeadingAngle);
    }
};

#endif