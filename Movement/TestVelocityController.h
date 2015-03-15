#ifndef TEST_MOVEMENT_STRATEGY_H
#define TEST_MOVEMENT_STRATEGY_H

#include <math.h>

#include "../Utilities/MathLib/Types.h"
#include "IVelocityController.h"

class TestVelocityController : public IVelocityController {
private:
    f64 linearVelocity;
    f64 angularVelocity;

    TestVelocityController(const TestVelocityController&);

    //"�������" ��������: k1 = 1.0, k2 = 10.0, beta = 0.4, lambda = 2.0
    //�������� k1, ����� �������� ����������
    const f64 k1 = 2.0;
    const f64 k2 = 10.0;
    const f64 beta = 0.4;
    const f64 lambda = 2.0;
    const f64 maxVelocity = 4.0;

    f64 curvature;

    // r - distanceToTarget
    // delta - headingAngle
    // theta - targetHeadingAngle
    void computeCurvature(f64 r, f64 delta, f64 theta) {
        curvature = -(1.0 / r) * (k2*(delta - atan(-k1*theta)) +
            (1 + k1 / (1 + k1*k1*theta*theta))*sin(delta));
    }

    void computeLinearVelocity(f64 r, f64 delta, f64 theta) {        
        linearVelocity = maxVelocity / (1 + beta*pow(abs(curvature), lambda));
    }

    void computeAngularVelocity(f64 r, f64 delta, f64 theta) {
        angularVelocity = linearVelocity * curvature;
    }

public:
    TestVelocityController() :
    linearVelocity(0.0),
    angularVelocity(0.0) {}

    f64 getLinearVelocity() const { return linearVelocity; }
    f64 getAngularVelocity() const { return angularVelocity; }

    void run(f64 distanceToTarget, f64 headingAngle,
        f64 targetHeadingAngle) {
        computeCurvature(distanceToTarget, headingAngle,
            targetHeadingAngle);
        computeLinearVelocity(distanceToTarget, headingAngle,
            targetHeadingAngle);
        computeAngularVelocity(distanceToTarget, headingAngle,
            targetHeadingAngle);
    }
};

#endif