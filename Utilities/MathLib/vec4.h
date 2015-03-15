#ifndef VEC4_H
#define VEC4_H 

#include <math.h>

#include "Types.h"
#include "..\Debug.h"

class vec2;
class vec3;

class vec4 {
public:
    f64 x, y, z, w;

    inline vec4()              {}
    inline vec4(f64 x, f64 y, f64 z, f64 w)  { this->x = x; this->y = y; this->z = z; this->w = w; }
    inline vec4(const vec4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    inline vec4(const vec3& xyz, f64 w);
    inline vec4(f64 x, const vec3& yzw);
    inline vec4(const vec2& xy, f64 z, f64 w);
    inline vec4(f64 x, const vec2& yz, f64 w);
    inline vec4(f64 x, f64 y, const vec2& zw);

    vec4& operator=(const vec4&);

    inline f64   length() const;
    vec4& normalize();

    inline f64  operator[](const size_type i) const;
    inline f64& operator[](const size_type i);

    inline vec4& operator+=(const vec4&);
    inline vec4& operator-=(const vec4&);

    template<class T>
    inline vec4& operator*=(const T&);
    template<class T>
    inline vec4& operator/=(const T&);

    friend        vec4 normalize(const vec4&);
    friend inline f64  dotProduct(const vec4&, const vec4&);

    friend inline const vec4& operator+(const vec4&);
    friend inline       vec4  operator-(const vec4&);
    friend inline       vec4  operator+(const vec4&, const vec4&);
    friend inline       vec4  operator-(const vec4&, const vec4&);
    friend inline       bool  operator==(const vec4&, const vec4&);
    friend inline       bool  operator!=(const vec4&, const vec4&);

    template<class T>
    friend inline vec4 operator*(const T&, const vec4&);
    template<class T>
    friend inline vec4 operator/(const vec4&, const T&);
};

vec4& vec4::operator=(const vec4& vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
    w = vector.w;
    return *this;
}

f64 vec4::length() const {
    return (f64)sqrt(x*x + y*y + z*z + w*w);
}

vec4& vec4::normalize() {
    const f64 len = length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;
    return *this;
}

f64 vec4::operator[](size_type i) const {
    ASSERT(i < 4);
    return *(&x + i);
}

f64& vec4::operator[](size_type i) {
    ASSERT(i < 4);
    return *(&x + i);
}

vec4& vec4::operator+=(const vec4& vector) {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    w += vector.w;
    return *this;
}

vec4& vec4::operator-=(const vec4& vector) {
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    w -= vector.w;
    return *this;
}

template<class T>
vec4& vec4::operator*=(const T& scalar) {
    x *= f64(scalar);
    y *= f64(scalar);
    z *= f64(scalar);
    w *= f64(scalar);
    return *this;
}

template<class T>
vec4& vec4::operator/=(const T& scalar) {
    x /= f64(scalar);
    y /= f64(scalar);
    z /= f64(scalar);
    w /= f64(scalar);
    return *this;
}

vec4 normalize(const vec4& vector) {
    const f64 len = vector.length();
    return vec4(vector.x / len, vector.y / len, vector.z / len, vector.w / len);
}

f64 dotProduct(const vec4& vector1, const vec4& vector2) {
    return vector1.x*vector2.x +
        vector1.y*vector2.y +
        vector1.z*vector2.z +
        vector1.w*vector2.w;
}

const vec4& operator+(const vec4& vector) {
    return vector;
}

vec4 operator-(const vec4& vector) {
    return vec4(-vector.x, -vector.y, -vector.z, -vector.w);
}

vec4 operator+(const vec4& vector1, const vec4& vector2) {
    return vec4(vector1.x + vector2.x, vector1.y + vector2.y,
        vector1.z + vector2.z, vector1.w + vector2.w);
}

vec4 operator-(const vec4& vector1, const vec4& vector2) {
    return vec4(vector1.x - vector2.x, vector1.y - vector2.y,
        vector1.z - vector2.z, vector1.w - vector2.w);
}

bool operator==(const vec4& vector1, const vec4& vector2) {
    return vector1.x == vector2.x && vector1.y == vector2.y &&
        vector1.z == vector2.z && vector1.w == vector2.w;
}

bool operator!=(const vec4& vector1, const vec4& vector2) {
    return !(vector1 == vector2);
}

template<class T>
vec4 operator*(const T& scalar, const vec4& vector) {
    return vec4(f64(scalar) * vector.x, f64(scalar) * vector.y,
        f64(scalar) * vector.z, f64(scalar) * vector.w);
}

template<class T>
vec4 operator/(const vec4& vector, const T& scalar) {
    return vec4(vector.x / f64(scalar), vector.y / f64(scalar),
        vector.z / f64(scalar), vector.w / f64(scalar));
}

#endif