#pragma once
#include "../math/matrix/matrix4x4.hpp"

class ViewMatrix {
public:
	ViewMatrix() = delete;

	SCHEMA(matrix4x4, 0x0, matrix);
};