#include "color.hpp"

Color::Color() {
	colors[0] = 0;
	colors[1] = 0;
	colors[2] = 0;
	colors[3] = 0;
}

void Color::set_color(int r, int g, int b, int a) {
	colors[0] = static_cast<unsigned char>(r);
	colors[1] = static_cast<unsigned char>(g);
	colors[2] = static_cast<unsigned char>(b);
	colors[3] = static_cast<unsigned char>(a);
}

void Color::set_color(float r, float g, float b, float a) {
	colors[0] = static_cast<unsigned char>(r * 255.0f);
	colors[1] = static_cast<unsigned char>(g * 255.0f);
	colors[2] = static_cast<unsigned char>(b * 255.0f);
	colors[3] = static_cast<unsigned char>(a * 255.0f);
}

void Color::get_color(int& r, int& g, int& b, int& a) const {
	r = colors[0];
	g = colors[1];
	b = colors[2];
	a = colors[3];
}

ImColor Color::get_color() const {
	return ImColor(
		r(),
		g(),
		b(),
		a()
	);
}

Color::Color(int r, int g, int b, int a) {
	set_color(r, g, b, a);
}

Color::Color(float r, float g, float b, float a) {
	set_color(r, g, b, a);
}

bool Color::operator==(const Color& clr) const {
	return (*((int*)this) == *((int*)&clr));
}

bool Color::operator!=(const Color& clr) const {
	return !(operator==(clr));
}

Color& Color::operator=(const Color& clr) {
	set_color(clr.r(), clr.g(), clr.b(), clr.a());
	return *this;
}
