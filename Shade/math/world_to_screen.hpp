#pragma once
#include "../sdk/math/vector.hpp"

namespace math {
	bool world_to_screen(const vector_3d& in, vector_2d& out);
}