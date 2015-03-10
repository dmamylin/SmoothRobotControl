#ifndef MATH_LIB_H
#define MATH_LIB_H

#include <math.h>

template<class T>
void swap(T& a, T& b) {
    T c = b;
    b = a;
    a = c;
}

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "point2.h"
#include "mat2.h"

typedef point2<s32> point2i;
typedef point2<vec2> point2vec2;

template<class T>
inline T max(const T& a, const T& b) {
    return a <= b ? b : a;
}

template<class T>
inline T min(const T& a, const T& b) {
    return a <= b ? a : b;
}

inline f64 degToRad(f64 deg) {
    return deg * M_PI / 180.0;
}

inline f64 radToDeg(f64 rad) {
    return rad * 180.0 / M_PI;
}

vec4::vec4(const vec3& xyz, f64 w) {
    x = xyz.x;
    y = xyz.y;
    z = xyz.z;
    this->w = w;
}
vec4::vec4(f64 x, const vec3& yzw) {
    this->x = x;
    y = yzw.x;
    z = yzw.y;
    w = yzw.z;
}

vec4::vec4(const vec2& xy, f64 z, f64 w) {
    x = xy.x;
    y = xy.y;
    this->z = z;
    this->w = w;
}

vec4::vec4(f64 x, const vec2& yz, f64 w) {
    this->x = x;
    y = yz.x;
    z = yz.y;
    this->w = w;
}

vec4::vec4(f64 x, f64 y, const vec2& zw) {
    this->x = x;
    this->y = y;
    z = zw.x;
    w = zw.y;
}

vec3::vec3(const vec2& xy, f64 z) {
    this->x = xy.x;
    this->y = xy.y;
    this->z = z;
}

vec3::vec3(f64 x, const vec2& yz) {
    this->x = x;
    this->y = yz.x;
    this->z = yz.y;
}

template<class T>
vec2::vec2(const point2<T>& point) {
    x = (f64)point.x;
    y = (f64)point.y;
}

template<class T>
point2<T>::point2(const vec2& v) {
    x = (T)v.x;
    y = (T)v.y;
}

mat2::mat2(const vec2& column1, const vec2& column2) {
    data[0] = column1.x;
    data[1] = column2.x;
    data[2] = column1.y;
    data[3] = column2.y;
}

vec2 operator*(const mat2& mat, const vec2& vec) {
    return vec2(mat.data[0] * vec.x + mat.data[1] * vec.y,
        mat.data[2] * vec.x + mat.data[3] * vec.y);
}

inline mat2 rotationMatrix2D(f64 angleRad) {
    f64 cosa = cos(angleRad);
    f64 sina = sin(angleRad);
    return mat2(cosa, -sina,
                sina, cosa);
}

inline mat2 identityMatrix2D() {
    return mat2(1.0, 1.0,
                0.0, 1.0);
}

#endif