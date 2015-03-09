#ifndef UTILITIES_H
#define UTILITIES_H

#include <math.h>

#include "debug.h"
#include "MathLib.h"
#include "SDL2Types.h"
#include "ColorRGB.h"

vec3 fromGlobalToLocal(const vec2& robotPosition, const vec2& targetPosition,
    const vec2& robotDirection, const vec2& targetDirection) {
    vec2 polarAxis = targetPosition - robotPosition;
    vec2 normal(-polarAxis.y, polarAxis.x);

    // delta - robot's heading angle
    // theta - target's heading angle
    f64 cosTheta = dotProduct(polarAxis, targetDirection) / 
        (polarAxis.length() * targetDirection.length());
    f64 cosDelta = dotProduct(polarAxis, robotDirection) /
        (polarAxis.length() * robotDirection.length());

    f64 theta = acos(cosTheta);
    f64 delta = acos(cosDelta);

    theta = dotProduct(targetDirection, normal) >= 0.0 ? theta : -theta;
    delta = dotProduct(robotDirection, normal) >= 0.0 ? delta : -delta;

    return vec3(polarAxis.length(), delta, theta);
}

#endif