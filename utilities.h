#ifndef UTILITIES_H
#define UTILITIES_H

#include <math.h>

#include "debug.h"
#include "point2.h"
#include "MathLib.h"
#include "SDL2Types.h"
#include "ColorRGB.h"

point2i fromScreenCoords(const point2i& pointOnScreen, const point2i& newCenter) {
    int newX = pointOnScreen.x - newCenter.x;
    int newY = newCenter.y - pointOnScreen.y;

    return point2i(newX, newY);
}

point2i toScreenCoords(const point2i& oldPoint, const point2i& oldCenter) {
    int newX = oldPoint.x + oldCenter.x;
    int newY = oldCenter.y - oldPoint.y;

    return point2i(newX, newY);
}

vec3 fromGlobalToLocal(const vec2& robotPosition, const vec2& targetPosition,
    const vec2& robotDirection, const vec2& targetDirection) {
    vec2 polarAxis = targetPosition - robotPosition;
    vec2 normal(-polarAxis.y, polarAxis.x);

    // delta - robot's heading angle
    // theta - target's heading angle
    double cosTheta = dotProduct(polarAxis, targetDirection) / 
        (polarAxis.length() * targetDirection.length());
    double cosDelta = dotProduct(polarAxis, robotDirection) /
        (polarAxis.length() * robotDirection.length());

    double theta = acos(cosTheta);
    double delta = acos(cosDelta);

    theta = dotProduct(targetDirection, normal) >= 0.0 ? theta : -theta;
    delta = dotProduct(robotDirection, normal) >= 0.0 ? delta : -delta;

    return vec3(polarAxis.length(), delta, theta);
}

#endif