#ifndef UTILITIES_H
#define UTILITIES_H

#include <math.h>

#include "point2.h"
#include "vec2.h"
#include "types.h"
#include "ColorRGB.h"

template<class T>
point2<T>::point2(const vec2& v) {
    x = (T)v.x;
    y = (T)v.y;
}

typedef point2<vec2> point2vec2;
typedef point2<int> point2i;

template<class T>
inline T max(const T& a, const T& b) {
    return a <= b ? b : a;
}

template<class T>
inline T min(const T& a, const T& b) {
    return a <= b ? a : b;
}

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

#endif