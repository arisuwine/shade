#pragma once
using vec_t = float;

struct vector_2d {
	vec_t x, y;
	vector_2d() : x(0), y(0) {}
	vector_2d(vec_t _x, vec_t _y) : x(_x), y(_y) {}
	vector_2d(const vector_2d& vec) : x(vec.x), y(vec.y) {}

	vector_2d operator=(float v) const {
		return vector_2d(v, v);
	}

	vector_2d operator+(const vector_2d& v) const {
		return vector_2d(x + v.x, y + v.y);
	}

	vector_2d operator-(float v) const {
		return vector_2d(x - v, y - v);
	}
};