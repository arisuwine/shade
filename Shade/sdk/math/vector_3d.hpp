#pragma once
#include <cmath>

using vec_t = float;

struct Vector3D {
	vec_t x, y, z;
	Vector3D() : x(0), y(0), z(0) {}
	Vector3D(vec_t _x, vec_t _y, vec_t _z) : x(_x), y(_y), z(_z) {}
	Vector3D(const Vector3D& vec) : x(vec.x), y(vec.y), z(vec.z) {}

	Vector3D operator+(const Vector3D& v) const {
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}

	Vector3D operator+(float v) const {
		return Vector3D(x + v, y + v, z + v);
	}

	Vector3D operator-(const Vector3D& v) const {
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}

	Vector3D operator-(float v) const {
		return Vector3D(x - v, y - v, z - v);
	}

	Vector3D operator-(void) const {
		return Vector3D(-x, -y, -z);
	}

	Vector3D operator*(const Vector3D& v) const {
		return Vector3D(x * v.x, y * v.y, z * v.z);
	}

	Vector3D operator*(float v) const {
		return Vector3D(x * v, y * v, z * v);
	}

	Vector3D operator/(const Vector3D& v) const {
		return Vector3D(x / v.x, y / v.y, z / v.z);
	}

	Vector3D operator/(float v) const {
		return Vector3D(x / v, y / v, z / v);
	}

	Vector3D& operator+=(const Vector3D& v) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	Vector3D& operator+=(float v) {
		x += v; y += v; z += v;
		return *this;
	}

	Vector3D& operator-=(const Vector3D& v) {
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	Vector3D& operator-=(float v) {
		x -= v; y -= v; z -= v;
		return *this;
	}

	Vector3D& operator*=(const Vector3D& v) {
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}

	Vector3D& operator*=(float v) {
		x *= v; y *= v; z *= v;
		return *this;
	}

	Vector3D& operator/=(const Vector3D& v) {
		x /= v.x; y /= v.y; z /= v.z;
		return *this;
	}

	Vector3D& operator/=(float v) {
		x /= v; y /= v; z /= v;
		return *this;
	}

	float operator[](size_t i) const {
		return ((float*)this)[i];
	}

	float& operator[](size_t i) {
		return ((float*)this)[i];
	}

	bool IsZero() const {
		if (x == 0.0f && y == 0.0f && z == 0.0f)
			return true;

		return false;
	}

	float Length() const {
		return sqrt(x * x + y * y + z * z);
	}

	float Normalize() const {
		Vector3D res = *this;
		float length = res.Length();

		if (length != 0.0f)
			res /= length;
		else
			res[0] = res[1] = res[2] = 0.0f;

		return length;
	}

	Vector3D Cross(const Vector3D& v) const {
		return Vector3D(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}
};