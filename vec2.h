#ifndef VEC2_H
#define VEC2_H

#include <math.h>

class vec2
{
	public:
		double x, y;

        vec2() : x(0.0f), y(0.0f) { }
        vec2(double X, double Y) : x(X), y(Y) { }
        vec2(const vec2& v) : x(v.x), y(v.y) { }

        friend bool operator == (const vec2&, const vec2&);
        friend bool operator != (const vec2&, const vec2&);
        friend const vec2 operator + (const vec2&); //Unary
		friend vec2 operator + (const vec2&, const vec2&);
		friend vec2 operator + (const vec2&, const double);
		friend vec2 operator + (const double, const vec2&);
		friend const vec2 operator - (const vec2&); //Unary
		friend vec2 operator - (const vec2&, const vec2&);
		friend vec2 operator - (const vec2&, const double);
		friend vec2 operator - (const double, const vec2&);
		friend vec2 operator * (const vec2&, const double);
		friend double operator * (const vec2&, const vec2&);
		friend vec2 operator * (const double, const vec2&);
		friend vec2 operator / (const vec2&, const double);
		friend vec2 operator / (const double, const vec2&);

        inline double& operator [] (int ind) { return *(&x + ind); }
        inline double operator [] (int ind) const { return *(&x + ind); }
        void operator = (const vec2&);
		void operator /= (const double);
		void operator *= (const double);
		void operator += (const double);
		void operator -= (const double);
		void operator += (const vec2&);
		void operator -= (const vec2&);

        inline double Length(void) const { return sqrt(x * x + y * y); }
        void Normalize(void);
};

inline bool operator == (const vec2& a, const vec2& b)
{
    return ( (a.x == b.x) && (a.y == b.y) );
}

inline bool operator != (const vec2& a, const vec2& b)
{
    return !(a == b);
}

inline const vec2 operator + (const vec2& v)
{
    return v;
}

inline vec2 operator + (const vec2& a, const vec2& b)
{
	return vec2(a.x + b.x, a.y + b.y);
}

inline vec2 operator + (const vec2& v, const double k)
{
	return vec2(v.x + k, v.y + k);
}

inline vec2 operator + (const double k, const vec2& v)
{
	return v + k;
}

inline const vec2 operator - (const vec2& v)
{
	return vec2(-v.x, -v.y);
}

inline vec2 operator - (const vec2& a, const vec2& b)
{
	return vec2(a.x - b.x, a.y - b.y);
}
inline vec2 operator - (const vec2& v, const double k)
{
	return vec2(v.x - k, v.y - k);
}

inline vec2 operator - (const double k, const vec2& v)
{
	return v - k;
}

inline vec2 operator * (const vec2& v, const double k)
{
	return vec2(v.x * k, v.y * k);
}

inline double operator * (const vec2& v0, const vec2& v1)
{
	return (v0.x * v1.x + v0.y * v1.y);
}

inline vec2 operator * (const double k, const vec2& v)
{
	return v * k;
}

inline vec2 operator / (const vec2& v, const double k)
{
	return vec2(v.x / k, v.y / k);
}

inline vec2 operator / (const double k, const vec2& v)
{
	return v / k;
}

inline void vec2::operator = (const vec2& v)
{
	x = v.x;
	y = v.y;
}

inline void vec2::operator /= (const double k)
{
	x /= k;
	y /= k;
}

inline void vec2::operator *= (const double k)
{
	x *= k;
	y *= k;
}

inline void vec2::operator += (const double k)
{
	x += k;
	y += k;
}

inline void vec2::operator -= (const double k)
{
	x -= k;
	y -= k;
}

inline void vec2::operator += (const vec2& v)
{
	(*this) = (*this) + v;
}

inline void vec2::operator -= (const vec2& v)
{
	(*this) = (*this) - v;
}

inline void vec2::Normalize(void)
{
    (*this) /= Length();
}

#endif
