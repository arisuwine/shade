#pragma once

struct color {
	float r, g, b, a;
	color(float _r, float _g, float _b, float _a = 255.0f) : r(_r), g(_g), b(_b), a(_a) {}
};