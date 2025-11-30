#pragma once
#include "imgui.h"

class color {
private:
	unsigned char colors[4];

public:
	color();
	color(int r, int g, int b, int a = 255);
	color(float r, float g, float b, float a = 1.0f);

	explicit color(unsigned long hex) {
		colors[2] = (unsigned char)((hex & 0x000000FF) >> (0 * 8));
		colors[1] = (unsigned char)((hex & 0x0000FF00) >> (1 * 8));
		colors[0] = (unsigned char)((hex & 0x00FF0000) >> (2 * 8));
		colors[3] = (unsigned char)((hex & 0xFF000000) >> (3 * 8));
	}

	inline int r() const { return colors[0]; }
	inline int g() const { return colors[1]; }
	inline int b() const { return colors[2]; }
	inline int a() const { return colors[3]; }

	inline void set_color(int r, int g, int b, int a = 255);
	inline void set_color(float r, float g, float b, float a = 1.0f);
	void get_color(int& r, int& g, int& b, int& a) const;
	ImColor get_color() const;

	unsigned char& operator[](size_t index) {
		return colors[index];
	}

	const unsigned char& operator[](size_t index) const {
		return colors[index];
	}

	bool operator==(const color& clr) const;
	bool operator!=(const color& clr) const;
	color& operator=(const color& clr);
};