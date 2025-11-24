#pragma once
#include "../math/math.hpp"
#include "../modules.hpp"
#include "../signatures.hpp"

class ViewMatrix {
public:
	ViewMatrix() = delete;

	SCHEMA(matrix4x4, 0x0, matrix);
};