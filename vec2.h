#ifndef VEC2_H
#define VEC2_H 

#include "SDL2Types.h"
#include "debug.h"

class vec2 {            
public:
    f64 x, y;

    inline vec2()              {}
    inline vec2(f64 x, f64 y)  { this->x = x; this->y = y; }
    inline vec2(const vec2& v) { x = v.x; y = v.y; }

    vec2& operator=(const vec2&);

    inline f64   length() const;
            vec2& normalize();

    inline f64  operator[](const size_type i) const;
    inline f64& operator[](const size_type i);

    inline vec2& operator+=(const vec2&);
    inline vec2& operator-=(const vec2&);

    template<class T>
    inline vec2& operator*=(const T&);
    template<class T>
    inline vec2& operator/=(const T&);

    friend        vec2 normalize(const vec2&);
    friend inline f64  dotProduct(const vec2&, const vec2&);

    friend inline const vec2& operator+(const vec2&);
    friend inline       vec2  operator-(const vec2&);
    friend inline       vec2  operator+(const vec2&, const vec2&);
    friend inline       vec2  operator-(const vec2&, const vec2&);
    friend inline       bool  operator==(const vec2&, const vec2&);
    friend inline       bool  operator!=(const vec2&, const vec2&);

    template<class T>
    friend inline vec2 operator*(const T&, const vec2&);
    template<class T>
    friend inline vec2 operator/(const vec2&, const T&);
};

vec2& vec2::operator=(const vec2& vector) {
    x = vector.x;
    y = vector.y;
    return *this;
}

f64 vec2::length() const {
    return (f64)sqrt(x*x + y*y);
}

vec2& vec2::normalize() {
    const f64 len = length();
    x /= len;
    y /= len;
    return *this;
}

f64 vec2::operator[](size_type i) const {
    ASSERT(i < 2);
    return *(&x + i);
}

f64& vec2::operator[](size_type i) {
    ASSERT(i < 2);
    return *(&x + i);
}

vec2& vec2::operator+=(const vec2& vector) {
    x += vector.x;
    y += vector.y;
    return *this;
}

vec2& vec2::operator-=(const vec2& vector) {
    x -= vector.x;
    y -= vector.y;
    return *this;
}

template<class T>
vec2& vec2::operator*=(const T& scalar) {
    x *= f64(scalar);
    y *= f64(scalar);
    return *this;
}

template<class T>
vec2& vec2::operator/=(const T& scalar) {
    x /= f64(scalar);
    y /= f64(scalar);
    return *this;
}

vec2 normalize(const vec2& vector) {
    const f64 len = vector.length();
    return vec2(vector.x / len, vector.y / len);
}

f64 dotProduct(const vec2& vector1, const vec2& vector2) {
    return vector1.x*vector2.x +
            vector1.y*vector2.y;
}

const vec2& operator+(const vec2& vector) {
    return vector;
}

vec2 operator-(const vec2& vector) {
    return vec2(-vector.x, -vector.y);
}

vec2 operator+(const vec2& vector1, const vec2& vector2) {
    return vec2(vector1.x + vector2.x, vector1.y + vector2.y);
}

vec2 operator-(const vec2& vector1, const vec2& vector2) {
    return vec2(vector1.x - vector2.x, vector1.y - vector2.y);
}

bool operator==(const vec2& vector1, const vec2& vector2) {
    return vector1.x == vector2.x && vector1.y == vector2.y;
}

bool operator!=(const vec2& vector1, const vec2& vector2) {
    return !(vector1 == vector2);
}

template<class T>
vec2 operator*(const T& scalar, const vec2& vector) {
    return vec2(f64(scalar) * vector.x, f64(scalar) * vector.y);
}

template<class T>
vec2 operator/(const vec2& vector, const T& scalar) {
    return vec2(vector.x / f64(scalar), vector.y / f64(scalar));
}

#endif