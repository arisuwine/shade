#pragma once
#include "../math/math.hpp"
#include "../modules.hpp"
#include "../signatures.hpp"

class ViewMatrix {
public:
	ViewMatrix() = delete;

	inline matrix4x4 get_matrix() {
		return *reinterpret_cast<matrix4x4*>(THIS_ADDR);
	}
};