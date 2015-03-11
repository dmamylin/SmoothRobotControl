#ifndef MAT2_H
#define MAT2_H

#include <math.h>

#include "types.h"
#include "debug.h"

class vec2;

class mat2 {
private:
    f64 data[4];

public:
    inline mat2(f64 a11, f64 a12, f64 a21, f64 a22) {
        data[0] = a11;
        data[1] = a12;
        data[2] = a21;
        data[3] = a22;
    }
    inline mat2(const mat2& other) {
        for (int i = 0; i < 4; i++) {
            data[i] = other.data[i];
        }
    }
    mat2(const vec2& column1, const vec2& column2);

    inline f64 determinant() const {
        return data[0] * data[3] - data[1] * data[2];
    }
    inline f64 trace() const {
        return data[0] + data[3];
    }
    inline mat2& transpose() {
        swap(data[1], data[2]);
        return *this;
    }

    // Get i'th column
    inline mat2 operator+() const {
        return *this;
    }
    inline mat2 operator-() const {
        return mat2(-data[0], -data[1],
                    -data[2], -data[3]);
    }
    inline const vec2 operator[](size_type i) const {
        ASSERT(i < 2);
        return vec2(data[0 + i % 2], data[2 + i % 2]);
    }
    /*inline vec2& operator[](size_type i) {
        ASSERT(i < 2);
        return vec2(data[0 + i % 2], data[2 + i % 2]);
    }*/
    inline mat2& operator=(const mat2& other) {
        for (int i = 0; i < 4; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }
    inline mat2& operator+=(const mat2& other) {
        return *this = *this + other;
    }
    inline mat2& operator-=(const mat2& other) {
        return *this = *this - other;
    }
    inline mat2& operator*=(const mat2& other) {
        return *this = *this * other;
    }

    friend vec2 operator*(const mat2&, const vec2&);
    friend inline mat2 operator*(const mat2& m1, const mat2& m2) {
        return mat2(m1.data[0]*m2.data[0] + m1.data[1]*m2.data[2],
            m1.data[0]*m2.data[1] + m1.data[1]*m2.data[3],
            m1.data[2]*m2.data[0] + m1.data[3]*m2.data[2],
            m1.data[2]*m2.data[1] + m1.data[3]*m2.data[3]);
    }
    friend inline mat2 operator+(const mat2& m1, const mat2& m2) {
        return mat2(m1.data[0] + m2.data[0], m1.data[1] + m2.data[1],
                    m1.data[2] + m2.data[2], m1.data[3] + m2.data[3]);
    }
    friend inline mat2 operator-(const mat2& m1, const mat2& m2) {
        return mat2(m1.data[0] - m2.data[0], m1.data[1] - m2.data[1],
            m1.data[2] - m2.data[2], m1.data[3] - m2.data[3]);
    }
    friend inline mat2 operator*(const f64 scalar, const mat2& mat) {
        return mat2(scalar*mat.data[0], scalar*mat.data[1],
                    scalar*mat.data[2], scalar*mat.data[3]);
    }

    friend inline mat2 transpose(const mat2& m) {
        return mat2(m.data[0], m.data[2],
                    m.data[1], m.data[3]);
    }
};

#endif