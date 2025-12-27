#pragma once
#include <cstdint>
#include "imgui.h"

class Color {
private:
	unsigned char colors[4];

public:
	Color();
	Color(int r, int g, int b, int a = 255);
	Color(float r, float g, float b, float a = 1.0f);

	explicit Color(unsigned long hex) {
		colors[0] = (unsigned char)((hex & 0x00FF0000) >> (2 * 8)); // R
		colors[1] = (unsigned char)((hex & 0x0000FF00) >> (1 * 8)); // G
		colors[2] = (unsigned char)((hex & 0x000000FF) >> (0 * 8)); // B
		colors[3] = (unsigned char)((hex & 0xFF000000) >> (3 * 8)); // A
	}

	unsigned long ByteColorRGBA() {
		return	(static_cast<unsigned long>(colors[0]) << (3 * 8)) | // R
				(static_cast<unsigned long>(colors[1]) << (2 * 8)) | // G
				(static_cast<unsigned long>(colors[2]) << (1 * 8)) | // B
				(static_cast<unsigned long>(colors[3]) << (0 * 8));  // A
	}

	inline int r() const { return colors[0]; }
	inline int g() const { return colors[1]; }
	inline int b() const { return colors[2]; }
	inline int a() const { return colors[3]; }

	void set_raw_color(uint32_t clr)
	{
		*((int*)this) = clr;
	}

	int get_raw_color() const
	{
		return *((int*)this);
	}

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

	bool operator==(const Color& clr) const;
	bool operator!=(const Color& clr) const;
	Color& operator=(const Color& clr);
};