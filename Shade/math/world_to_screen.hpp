#pragma once
#include "../sdk/math/vector.hpp"

namespace math {
	bool WorldToScreen(const vector_3d& in, vector_2d& out);
}