/*
* Vector2D.h
* Xue Cui
* 10.18.2015
* Desc:
*
*/
#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include <cmath>
#include <limits>
#include <assert.h>

#define UTL_PI 3.14159265358979323846
#define UTL_PI_DEGREE 180
#define UTL_ZERO 0
#define FOR_2X2_MATRIX for(i=0; i<=1; i++){for(j=0; j<=1; j++){
#define FOR_3X3_MATRIX for(i=0; i<=2; i++){for(j=1; j<=2; j++){
#define END_FOR }}
#define ROUND_COS abs(cos(radians)) <= numeric_limits<T>::epsilon() ? 0 : cos(radians)
#define ROUND_MINUS_COS abs(-cos(radians)) <= numeric_limits<T>::epsilon() ? 0 : -cos(radians)
#define ROUND_SIN abs(sin(radians)) <= numeric_limits<T>::epsilon() ? 0 : sin(radians)
#define ROUND_MINUS_SIN abs(-sin(radians)) <= numeric_limits<T>::epsilon() ? 0 : -sin(radians)
#define X_ROTATION_MATRIX { 1, 0, 0, 0, ROUND_COS, ROUND_SIN, 0, ROUND_MINUS_SIN, ROUND_COS }
#define Y_ROTATION_MATRIX { ROUND_COS, 0, ROUND_SIN, 0, 1, 0, ROUND_MINUS_SIN, 0, ROUND_COS }
#define Z_ROTATION_MATRIX { ROUND_COS, ROUND_SIN, 0, ROUND_MINUS_SIN, ROUND_COS, 0, 0, 0, 1 }

namespace VFXEpoch
{
	enum SIDE
	{
		LEFT, RIGHT, EQUAL
	};

	enum AXIS
	{
		X, Y, Z
	};

	template <class T>
	class Vector2D
	{
	public:
		T m_x;
		T m_y;

	public:
		Vector2D(){}
		Vector2D(T _x, T _y) : m_x(_x), m_y(_y){}
		Vector2D(const Vector2D& source) : m_x(source.m_x), m_y(source.m_y){}
		Vector2D& operator=(const Vector2D& source){ this->m_x = source.m_x; this->m_y = source.m_y; return *this; }
		Vector2D operator+(Vector2D& source){ return Vector2D(m_x + source.m_x, m_y + source.m_y); }
		Vector2D operator-(Vector2D& source){ return Vector2D(m_x - source.m_x, m_y - source.m_y); }
		Vector2D operator*(T coef){ return Vector2D(m_x * coef, m_y * coef); }
		Vector2D operator/(T coef){ return Vector2D(m_x / coef, m_y / coef); }
		Vector2D& operator+=(const Vector2D& source){ m_x += source.m_x; m_y += source.m_y; return *this; }
		Vector2D& operator-=(const Vector2D& source){ m_x -= source.m_x; m_y -= source.m_y; return *this; }
		Vector2D& operator*=(T coef){ m_x *= coef; m_y *= coef; return *this; }
		Vector2D& operator/=(T coef){ m_x / coef; m_y / coef; return *this; }

		T& operator[](int i)
		{
			assert(i < 0 || i > 1);

			if (0 == i)
				return m_x;
			else
				return m_y;
		}

		inline bool operator==(const Vector2D& source) const { return m_x == source.m_x && m_y == source.m_y ? true : false; }

		// Clockwise is positive while Counterclockwise is negtive
		void rotate(T degree)
		{
			T theta = T(-degree / UTL_PI_DEGREE * UTL_PI);
			T cosTheta = cos(theta);
			T sinTheta = sin(theta);

			T _x = m_x * cosTheta - m_y * sinTheta;
			T _y = m_x * sinTheta + m_y * cosTheta;

			m_x = _x;
			m_y = _y;
		}

		T length(){ return std::sqrt(m_x * m_x + m_y * m_y); }
		T dist(Vector2D v) { Vector2D v(v.m_x - m_x, v.m_y - m_y); return v.length(); }
		Vector2D& normalize(){ if (T(UTL_ZERO) == length()) return *this; *this *= (1.0f / length()); return *this; }
		static T dot(Vector2D v1, Vector2D v2) { return v1.m_x * v2.m_x + v1.m_y * v2.m_y; }
		static T det(Vector2D v1, Vector2D v2) { return (v1.m_x * v2.m_y) - (v1.m_y * v2.m_x); }
		static T getRadian(Vector2D v1, Vector2D v2) { v1.normalize(); v2.normalize(); return std::acos(dot(v1, v2) / (v1.length() * v2.length())); }
		static T getDegree(Vector2D v1, Vector2D v2) { v1.normalize(); v2.normalize(); return std::acos(dot(v1, v2) / (v1.length() * v2.length())) * T(UTL_PI_DEGREE / UTL_PI); }

		// This tells user if second vector is at the right side of the first vector or left, or equal.
		static SIDE isRightLeft(Vector2D vec1, Vector2D vec2)
		{
			T tmp;
			tmp = vec2.m_x;
			vec2.m_x = -vec2.m_y;
			vec2.m_y = tmp;

			T d = dot(vec1, vec2);

			if (d > 0)
				return RIGHT;
			else if (d < 0)
				return LEFT;
			else
				return EQUAL;
		}
	};

	typedef Vector2D<float> Vector2Df;
	typedef Vector2D<double> Vector2Dd;

	template <class T>
	class Vector3D
	{
	public:
		T m_x;
		T m_y;
		T m_z;

		Vector3D(){}
		Vector3D(T _x, T _y, T _z) : m_x(_x), m_y(_y), m_z(_z){}
		Vector3D(const Vector3D& source) : m_x(source.m_x), m_y(source.m_y), m_z(source.m_z){}
		Vector3D& operator=(const Vector3D& source){ this->m_x = source.m_x; this->m_y = source.m_y; this->m_z = source.m_z; return *this; }
		Vector3D operator+(Vector3D& source){ return Vector3D(m_x + source.m_x, m_y + source.m_y, m_z + source.m_z); }
		Vector3D operator-(Vector3D& source){ return Vector3D(m_x - source.m_x, m_y - source.m_y, m_z - source.m_z); }
		Vector3D operator*(T coef){ return Vector3D(m_x * coef, m_y * coef, m_z * coef); }
		Vector3D operator/(T coef){ return Vector3D(m_x / coef, m_y / coef, m_z / coef); }
		Vector3D& operator+=(const Vector3D& source){ m_x += source.m_x; m_y += source.m_y; m_z += source.m_z; return *this; }
		Vector3D& operator-=(const Vector3D& source){ m_x -= source.m_x; m_y -= source.m_y; m_z -= source.m_z; return *this; }
		Vector3D& operator*=(T coef){ m_x *= coef; m_y *= coef; m_z *= coef; return *this; }
		Vector3D& operator/=(T coef){ m_x /= coef; m_y /= coef; m_z /= coef; return *this; }

		T& operator[](int i)
		{
			assert(i >= 0 && i <= 2);

			if (0 == i)
				return m_x;
			else if (1 == i)
				return m_y;
			else
				return m_z;
		}

		inline bool operator==(const Vector3D& source) const { return (m_x == source.m_x && m_y == source.m_y && m_z == source.m_z) ? true : false; }
		T length(){ return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z); }
		T dist(Vector3D v) { Vector3D v(v.m_x - m_x, v.m_y - m_y, v.m_z - m_z); return v.length(); }
		Vector3D& normalize(){ if (T(UTL_ZERO) == length()) return *this; *this *= (1.0f / length()); return *this; }
		static T dot(Vector3D v1, Vector3D v2) { return v1.m_x * v2.m_x + v1.m_y * v2.m_y + v1.m_z * v2.m_z; }

		static Vector3D cross(Vector3D v1, Vector3D v2)
		{
			Vector3D result;
			result.m_x = v1.m_y * v2.m_z - v1.m_z * v2.m_y;
			result.m_y = v1.m_z * v2.m_x - v1.m_x * v2.m_z;
			result.m_z = v1.m_x * v2.m_y - v1.m_y * v2.m_x;

			return result;
		}

		static T getRadian(Vector3D v1, Vector3D v2) { v1.normalize(); v2.normalize(); return std::acos(dot(v1, v2) / (v1.length() * v2.length())); }
		static T getDegree(Vector3D v1, Vector3D v2) { v1.normalize(); v2.normalize(); return std::acos(dot(v1, v2) / (v1.length() * v2.length())) * T(UTL_PI_DEGREE / UTL_PI); }

		void rotate(AXIS axis, T degree)
		{
			T radians = T(degree * UTL_PI / UTL_PI_DEGREE);
			if (VFXEpoch::AXIS::X == axis)
			{
				T rotationMat[3 * 3] = X_ROTATION_MATRIX;

				Vector3D<T> vec(m_x, m_y, m_z);
				Vector3D<T> result(0, 0, 0);

				for (int i = 0; i != 3; i++)
				{
					T sum = 0;
					for (int j = 0; j != 3; j++)
					{
						sum += rotationMat[i * 3 + j] * vec[j];
					}
					result[i] = sum;
				}
				m_x = result[0];
				m_y = result[1];
				m_z = result[2];
			}
			else if (VFXEpoch::AXIS::Y == axis)
			{
				T rotationMat[3 * 3] = Y_ROTATION_MATRIX;
				Vector3D<T> vec(m_x, m_y, m_z);
				Vector3D<T> result(0, 0, 0);

				for (int i = 0; i != 3; i++)
				{
					T sum = 0;
					for (int j = 0; j != 3; j++)
					{
						sum += rotationMat[i * 3 + j] * vec[j];
					}
					result[i] = sum;
				}
				m_x = result[0];
				m_y = result[1];
				m_z = result[2];
			}
			else
			{
				T rotationMat[3 * 3] = Z_ROTATION_MATRIX;
				Vector3D<T> vec(m_x, m_y, m_z);
				Vector3D<T> result(0, 0, 0);

				for (int i = 0; i != 3; i++)
				{
					T sum = 0;
					for (int j = 0; j != 3; j++)
					{
						sum += rotationMat[i * 3 + j] * vec[j];
					}
					result[i] = sum;
				}
				m_x = result[0];
				m_y = result[1];
				m_z = result[2];
			}
		}
	};

	typedef Vector3D<float> Vector3Df;
	typedef Vector3D<double> Vector3Dd;
}

#endif