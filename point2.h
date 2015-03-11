#ifndef POINT2_H
#define POINT2_H

class vec2;

template<class T>
class point2
{
	public:
		T x, y;
		
		point2() { }
        point2(const T& X, const T& Y) : x(X), y(Y) { }
        point2(const vec2&);
		point2(const point2<T>& p) : x(p.x), y(p.y) { }
		
		point2<T>& operator=(const point2<T>& p) { 
			x = p.x;
			y = p.y;
			return *this;
		}

        point2<T>& operator+=(const point2<T>& p) {
            x += p.x;
            y += p.y;
            return *this;
        }

        point2<T>& operator-=(const point2<T>& p) {
            x -= p.x;
            y -= p.y;
            return *this;
        }

        point2<T>& operator*=(const T& scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
		
        inline friend bool operator==(const point2<F>& p) {
			return (x == p.x && y == p.y);
		}
		
        inline friend bool operator!=(const point2<F>& p) {
			return !((*this) == p);
		}

        inline friend point2<T> operator+(const point2<T>& lhs, const point2<T>& rhs) {
			return point2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
		}

        inline friend point2<T> operator-(const point2<T>& lhs, const point2<T>& rhs) {
			return point2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
		}

		inline friend point2<T> operator*(const T& scalar, const point2<T>& point) {
			return point2<T>(scalar * point.x, scalar * point.y);
		}
};

#endif