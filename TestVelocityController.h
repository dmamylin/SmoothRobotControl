#ifndef TEST_MOVEMENT_STRATEGY_H
#define TEST_MOVEMENT_STRATEGY_H

#include <math.h>

#include "SDL2Types.h"
#include "IVelocityController.h"

class TestVelocityController : public IVelocityController {
private:
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
    TestVelocityController() : IVelocityController() {}

    void run(f64 distanceToTarget, f64 headingAngle,
        f64 targetHeadingAngle) {
        computeCurvature(distanceToTarget, headingAngle,
            targetHeadingAngle);
        computeLinearVelocity(distanceToTarget, headingAngle,
            targetHeadingAngle);
        computeAngularVelocity(distanceToTarget, headingAngle,
            targetHeadingAngle);

        printf("Curvature: %.3lf linearVelocity: %.3lf angularVelocity: %.3lf\n",
            curvature, linearVelocity, angularVelocity);
        /*printf("Distance: %.3lf Delta: %.3lf Theta: %.3lf\n",
            distanceToTarget, radToDeg(headingAngle), radToDeg(targetHeadingAngle));*/
    }
};

#endif