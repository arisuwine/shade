#pragma once
#include <cmath>

using vec_t = float;

struct vector_3d {
	vec_t x, y, z;
	vector_3d() : x(0), y(0), z(0) {}
	vector_3d(vec_t _x, vec_t _y, vec_t _z) : x(_x), y(_y), z(_z) {}
	vector_3d(const vector_3d& vec) : x(vec.x), y(vec.y), z(vec.z) {}

	vector_3d operator+(const vector_3d& v) const {
		return vector_3d(x + v.x, y + v.y, z + v.z);
	}

	vector_3d operator+(float v) const {
		return vector_3d(x + v, y + v, z + v);
	}

	vector_3d operator-(const vector_3d& v) const {
		return vector_3d(x - v.x, y - v.y, z - v.z);
	}

	vector_3d operator-(float v) const {
		return vector_3d(x - v, y - v, z - v);
	}

	vector_3d operator-(void) const {
		return vector_3d(-x, -y, -z);
	}

	vector_3d operator*(const vector_3d& v) const {
		return vector_3d(x * v.x, y * v.y, z * v.z);
	}

	vector_3d operator*(float v) const {
		return vector_3d(x * v, y * v, z * v);
	}

	vector_3d operator/(const vector_3d& v) const {
		return vector_3d(x / v.x, y / v.y, z / v.z);
	}

	vector_3d operator/(float v) const {
		return vector_3d(x / v, y / v, z / v);
	}

	vector_3d& operator+=(const vector_3d& v) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	vector_3d& operator+=(float v) {
		x += v; y += v; z += v;
		return *this;
	}

	vector_3d& operator-=(const vector_3d& v) {
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	vector_3d& operator-=(float v) {
		x -= v; y -= v; z -= v;
		return *this;
	}

	vector_3d& operator*=(const vector_3d& v) {
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}

	vector_3d& operator*=(float v) {
		x *= v; y *= v; z *= v;
		return *this;
	}

	vector_3d& operator/=(const vector_3d& v) {
		x /= v.x; y /= v.y; z /= v.z;
		return *this;
	}

	vector_3d& operator/=(float v) {
		x /= v; y /= v; z /= v;
		return *this;
	}

	float operator[](size_t i) const {
		return ((float*)this)[i];
	}

	float& operator[](size_t i) {
		return ((float*)this)[i];
	}

	bool is_zero() const {
		if (x == 0.0f && y == 0.0f && z == 0.0f)
			return true;
		return false;
	}

	float length() const {
		return sqrt(x * x + y * y + z * z);
	}

	float normalize() const {
		vector_3d res = *this;
		float length = res.length();

		if (length != 0.0f)
			res /= length;
		else
			res[0] = res[1] = res[2] = 0.0f;

		return length;
	}

	vector_3d cross(const vector_3d& v) const {
		return vector_3d(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}
};