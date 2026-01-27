#pragma once
using vec_t = float;

struct Vector2D {
	vec_t x, y;
	Vector2D() : x(0), y(0) {}
	Vector2D(vec_t _x, vec_t _y) : x(_x), y(_y) {}
	Vector2D(const Vector2D& vec) : x(vec.x), y(vec.y) {}

	Vector2D operator=(float v) const {
		return Vector2D(v, v);
	}

	Vector2D operator+(const Vector2D& v) const {
		return Vector2D(x + v.x, y + v.y);
	}

	Vector2D operator-(float v) const {
		return Vector2D(x - v, y - v);
	}
};