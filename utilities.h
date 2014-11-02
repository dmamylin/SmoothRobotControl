#ifndef UTILITIES_H
#define UTILITIES_H

#include <math.h>

#include "deps/point2.h"
#include "deps/vec2.h"

template<class T>
point2<T>::point2(const vec2& v) {
    x = (T)v.x;
    y = (T)v.y;
}

typedef point2<vec2> point2vec2;
typedef point2<int> point2i;
typedef unsigned int u32;

template<class T>
T max(const T& a, const T& b) {
    return a <= b ? b : a;
}

template<class T>
T min(const T& a, const T& b) {
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

void setPixel(SDL_Surface* s, int x, int y, u32 color) {
    if (x >= 0 && x < s->w && y >= 0 && y < s->h)
    ((u32*)s->pixels)[y * s->w + x] = color;
}

void drawLine(SDL_Surface* s, int x1, int y1, int x2, int y2, u32 color) {
    int start, end, i; 
    double k, b; 
    int dx = x1 - x2;
    int dy = y1 - y2;

    if ( abs(dx) >= abs(dy) ) {
        start = min(x1, x2);
        end = max(x1, x2);

        k = ( (double)(y1 - y2) ) / dx;
        b = ( (double)(x1 * y2 - x2 * y1) ) / dx;

        for (i = start; i <= end; i++) {
            int y = (int)(k * i + b);

            setPixel(s, i, y, color);
        }
    } else {
        start = min(y1, y2);
        end = max(y1, y2);

        k = ( (double)(dx) ) / dy;
        b = -( (double)(x1 * y2 - x2 * y1) ) / dy;

        for (i = start; i <= end; i++) {
            int x = (int)(k*i + b);

            setPixel(s, x, i, color);
        }
    }
}

inline void drawLine(SDL_Surface* s, const point2i& p1, const point2i& p2, u32 color) {
    drawLine(s, p1.x, p1.y, p2.x, p2.y, color);
}

#endif