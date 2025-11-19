#pragma once
#include "../math/math.hpp"
#include "../modules.hpp"
#include "../signatures.hpp"

class view_matrix {
private:
	view_matrix() = delete;
	static uintptr_t handle;
	static inline uintptr_t get_address();

public:
	static matrix4x4 get_matrix();
};