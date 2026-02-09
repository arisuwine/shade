#pragma once

class CGlowObject {
public:
	float red, green, blue, alpha;
	void SetColor(int r, int g, int b, float a) {
		red = r / 255.f;
		green = g / 255.f;
		blue = b / 255.f;
		alpha = a;
	}
};