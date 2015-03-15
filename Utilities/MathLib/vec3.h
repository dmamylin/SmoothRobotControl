#ifndef VEC3_H
#define VEC3_H 

#include <math.h>

#include "Types.h"
#include "..\Debug.h"

class vec2;

class vec3 {
public:
    f64 x, y, z;

    inline vec3()              {}
    inline vec3(f64 x, f64 y, f64 z)  { this->x = x; this->y = y; this->z = z; }
    inline vec3(const vec3& v) { x = v.x; y = v.y; z = v.z; }
    inline vec3(const vec2& xy, f64 z);
    inline vec3(f64 x, const vec2& yz);

    vec3& operator=(const vec3&);

    inline f64   length() const;
    vec3& normalize();

    inline f64  operator[](const size_type i) const;
    inline f64& operator[](const size_type i);

    inline vec3& operator+=(const vec3&);
    inline vec3& operator-=(const vec3&);

    template<class T>
    inline vec3& operator*=(const T&);
    template<class T>
    inline vec3& operator/=(const T&);

    friend        vec3 normalize(const vec3&);
    friend inline f64  dotProduct(const vec3&, const vec3&);

    friend inline const vec3& operator+(const vec3&);
    friend inline       vec3  operator-(const vec3&);
    friend inline       vec3  operator+(const vec3&, const vec3&);
    friend inline       vec3  operator-(const vec3&, const vec3&);
    friend inline       bool  operator==(const vec3&, const vec3&);
    friend inline       bool  operator!=(const vec3&, const vec3&);

    template<class T>
    friend inline vec3 operator*(const T&, const vec3&);
    template<class T>
    friend inline vec3 operator/(const vec3&, const T&);
};

vec3& vec3::operator=(const vec3& vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
    return *this;
}

f64 vec3::length() const {
    return (f64)sqrt(x*x + y*y + z*z);
}

vec3& vec3::normalize() {
    const f64 len = length();
    x /= len;
    y /= len;
    z /= len;
    return *this;
}

f64 vec3::operator[](size_type i) const {
    ASSERT(i < 3);
    return *(&x + i);
}

f64& vec3::operator[](size_type i) {
    ASSERT(i < 3);
    return *(&x + i);
}

vec3& vec3::operator+=(const vec3& vector) {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

vec3& vec3::operator-=(const vec3& vector) {
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return *this;
}

template<class T>
vec3& vec3::operator*=(const T& scalar) {
    x *= f64(scalar);
    y *= f64(scalar);
    z *= f64(scalar);
    return *this;
}

template<class T>
vec3& vec3::operator/=(const T& scalar) {
    x /= f64(scalar);
    y /= f64(scalar);
    z /= f64(scalar);
    return *this;
}

vec3 normalize(const vec3& vector) {
    const f64 len = vector.length();
    return vec3(vector.x / len, vector.y / len, vector.z / len);
}

f64 dotProduct(const vec3& vector1, const vec3& vector2) {
    return vector1.x*vector2.x +
        vector1.y*vector2.y +
        vector1.z*vector2.z;
}

const vec3& operator+(const vec3& vector) {
    return vector;
}

vec3 operator-(const vec3& vector) {
    return vec3(-vector.x, -vector.y, -vector.z);
}

vec3 operator+(const vec3& vector1, const vec3& vector2) {
    return vec3(vector1.x + vector2.x, vector1.y + vector2.y,
        vector1.z + vector2.z);
}

vec3 operator-(const vec3& vector1, const vec3& vector2) {
    return vec3(vector1.x - vector2.x, vector1.y - vector2.y,
        vector1.z - vector2.z);
}

bool operator==(const vec3& vector1, const vec3& vector2) {
    return vector1.x == vector2.x && vector1.y == vector2.y &&
        vector1.z == vector2.z;
}

bool operator!=(const vec3& vector1, const vec3& vector2) {
    return !(vector1 == vector2);
}

template<class T>
vec3 operator*(const T& scalar, const vec3& vector) {
    return vec3(f64(scalar) * vector.x, f64(scalar) * vector.y,
        f64(scalar) * vector.z);
}

template<class T>
vec3 operator/(const vec3& vector, const T& scalar) {
    return vec3(vector.x / f64(scalar), vector.y / f64(scalar),
        vector.z / f64(scalar));
}

#endif